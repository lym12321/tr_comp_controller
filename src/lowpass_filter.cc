//
// Created by 15082 on 2026/6/1.
//

#include "filter/lowpass_filter.h"

#include <cassert>
#include <cmath>
#include <limits>
#include <numbers>

using namespace filter;

/**
 * @brief 低通滤波器
 * @param cut_frequency 模拟 RC 截止频率 (Hz)，经后向欧拉离散化
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
	if (!std::isfinite(cut_frequency) || !std::isfinite(sampling_frequency) ||
		cut_frequency <= 0 || sampling_frequency <= 0) {
		return;
	}
	const float coefficient = 1 / (1 + sampling_frequency /
		(2 * std::numbers::pi_v<float> * cut_frequency));
	if (std::isfinite(coefficient) && coefficient > 0 && coefficient <= 1) {
		filter_coe_ = coefficient;
	}
}

float low_pass_filter::update(float sample) {
	if (!std::isfinite(sample)) return std::numeric_limits<float>::quiet_NaN();
	current_out_ = (1-filter_coe_)*current_out_ + filter_coe_*sample;
	return current_out_;
}
