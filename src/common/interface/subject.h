#ifndef SUBJECT_H_
#define SUBJECT_H_

#include <functional>
#include <future>
#include <memory>
#include <stdint.h>
#include <vector>

template<typename T>
class Observable {
public:
    Observable() {};
    ~Observable() {};
    typedef std::function<void(T)> OnMessageFunc;

    void Subscribe(OnMessageFunc func) {
        subscribed_func_ = func;
    }

    void UnSubscribe() {
        subscribed_func_ = nullptr;
    }

    OnMessageFunc subscribed_func_;
};

template<typename T>
class Subject {
public:
    virtual ~Subject(){};
    virtual void Next(T message) {
        for (auto &observer : observers_) {
            if (observer && observer->subscribed_func_ != nullptr) {
                auto task = std::async(std::launch::async, observer->subscribed_func_, message);
            }
        }
    }

    virtual std::shared_ptr<Observable<T>> AsObservable() {
        auto observer = std::make_shared<Observable<T>>();
        observers_.push_back(observer);
        return observer;
    }

    virtual void UnSubscribe() {
        auto it = observers_.begin();
        while (it != observers_.end()) {
            it->reset();
            it = observers_.erase(it);
        }
    }

protected:
    std::vector<std::shared_ptr<Observable<T>>> observers_;

    void RemoveNullObservers() {
        auto new_end = std::remove_if(observers_.begin(), observers_.end(),
            [](const std::shared_ptr<Observable<T>>& observer) {
                return !observer;
            });
        observers_.erase(new_end, observers_.end());
    }
};

#endif
