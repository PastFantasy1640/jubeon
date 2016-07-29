#pragma once

#ifndef JUBEON_THEME_DROP_HPP
#define JUBEON_THEME_DROP_HPP

#include <SFML/Graphics.hpp>
#include <array>
#include <memory>
#include "Spring.hpp"

using namespace std;

namespace Theme {
	template<std::size_t S>
	class Drop : public sf::Shape {
	public:
		Drop(std::array<sf::Vector2f, S> points, unsigned int bezier_resolution)
			: centerPoint_(new Spring::Point()),
			bezier_resolution_(bezier_resolution)
		{
			centerPoint_->weight = Drop::CENTRER_WEIGHT;
			for (std::size_t i = 0; i < S; i++)
			{
				points_[i] = shared_ptr<Spring::Point>(new Spring::Point());
				points_[i]->position.x = points[i].x;
				points_[i]->position.y = points[i].y;
				points_[i]->weight = Drop::DEFAULT_WEIGHT;
				centerPoint_->position += points[i];
			}

			centerPoint_->position /= static_cast<float>(S);

			for (std::size_t i = 0; i < S; i++) {
				std::size_t endIdx = (i == S - 1) ? 0 : i + 1;
				springs_[i * 2] = shared_ptr<Spring>(new Spring(0.4, points_[i], points_[endIdx]));
				springs_[i * 2 + 1] = shared_ptr<Spring>(new Spring(0.4, centerPoint_, points_[endIdx]));
			}
		}

		
		void applyForce(sf::Vector2f force)
		{
			points_[0]->force += force;
			for (auto spring : springs_) { spring->update(); };
			for (auto point : points_) { point->update(); };
			this->update();
		}

		virtual std::size_t getPointCount() const {

			return S * bezier_resolution_;

		}

		// TODO: ベジェを利用して、曲線を描くようにする。
		// getPointCountでは S * ベジェの頂点数 を返せばおｋ
		virtual sf::Vector2f getPoint(std::size_t idx) const {
			size_t pidx = idx / bezier_resolution_;	//アクセスするpoint_[i]の点

			size_t pidxn = pidx + 1;					//アクセスするpoint_[i+1]の点
			if (pidxn == points_.size()) pidxn = 0;

			std::size_t pidxnn = pidxn + 1;
			if (pidxnn == points_.size()) pidxnn = 0;


			//開始点s
			sf::Vector2f s;
			s.x = (points_[pidx]->position + points_[pidxn]->position).x / 2.0f;
			s.y = (points_[pidx]->position + points_[pidxn]->position).y / 2.0f;

			//終了点e
			sf::Vector2f e;
			e.x = (points_[pidxn]->position + points_[pidxnn]->position).x / 2;
			e.y = (points_[pidxn]->position + points_[pidxnn]->position).y / 2;

			//コントロールポイントcp
			sf::Vector2f cp = points_[pidxn]->position;	//違うと思う。

			sf::Vector2f v1 = cp - s;
			sf::Vector2f v2 = e - cp;

			float t = static_cast<float>(idx) / static_cast<float>(bezier_resolution_) - static_cast<float>(pidx);
			return (v1 * t + (v1 * (1 - t) + v2 * t) * t + s);
			//return sf::Vector2f(0, 0);

		}

	private:
		Drop();
		static const int DEFAULT_WEIGHT = 120;
		static const int CENTRER_WEIGHT = 99999;
		const unsigned int bezier_resolution_;
		std::array<std::shared_ptr<Spring::Point>, S> points_;
		std::shared_ptr<Spring::Point> centerPoint_;
		std::array<std::shared_ptr<Spring>, S * 2> springs_;
	};
};

#endif