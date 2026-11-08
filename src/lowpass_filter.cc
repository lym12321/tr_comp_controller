//
// Created by 15082 on 2026/6/1.
//

#include "filter/lowpass_filter.h"

#include <cassert>
#include <cmath>
#include <numbers>

using namespace filter;

/**
 * @brief 低通滤波器
 * @param cut_frequency 截止频率（-3dB增益点）
 * @param sampling_frequency 采样频率
 */
low_pass_filter::low_pass_filter(float cut_frequency, float sampling_frequency) {
	assert(std::isfinite(cut_frequency) && std::isfinite(sampling_frequency) &&
		cut_frequency > 0 && sampling_frequency > 0);
	set_params(cut_frequency, sampling_frequency);
}

void low_pass_filter::clear() {
	current_out_ = 0;
}

void low_pass_filter::set_params(float cut_frequency, float sampling_frequency) {
	filter_coe_ = 1 / (1 + sampling_frequency / (2 * std::numbers::pi_v<float> * cut_frequency));
}

float low_pass_filter::update(float sample) {
	current_out_ = (1-filter_coe_)*current_out_ + filter_coe_*sample;
	return current_out_;
}
