#ifndef CUSTOMIZED_VIDEO_ENCODER_FACTORY_H_
#define CUSTOMIZED_VIDEO_ENCODER_FACTORY_H_

#include "data_channel_subject.h"

#include <api/video_codecs/sdp_video_format.h>
#include <api/video_codecs/video_encoder.h>
#include <api/video_codecs/video_encoder_factory.h>

#include <memory>
#include <vector>

std::unique_ptr<webrtc::VideoEncoderFactory> CreateCustomizedVideoEncoderFactory(
    std::shared_ptr<DataChannelSubject> data_channel_subject);

class CustomizedVideoEncoderFactory : public webrtc::VideoEncoderFactory
{
public:
    CustomizedVideoEncoderFactory(
        std::shared_ptr<DataChannelSubject> data_channel_subject)
        : data_channel_subject_(data_channel_subject){};
    ~CustomizedVideoEncoderFactory(){};

    std::vector<webrtc::SdpVideoFormat> GetSupportedFormats() const override;

    std::unique_ptr<webrtc::VideoEncoder> CreateVideoEncoder(
        const webrtc::SdpVideoFormat &format) override;

private:
    std::shared_ptr<DataChannelSubject> data_channel_subject_;
};

#endif // CUSTOMIZED_VIDEO_ENCODER_FACTORY_H_