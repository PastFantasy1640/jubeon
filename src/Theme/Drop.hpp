#pragma once
#include <SFML/Graphics.hpp>
#include <array>
#include <memory>
#include "Spring.hpp"

namespace Theme {
	template<std::size_t S>
	class Drop : public sf::Shape {
	public:
		Drop(std::array<sf::Vector2f, S> points)
			:centerPoint_(new Spring::Point()) {
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
		};
		void applyForce(sf::Vector2f force) {
			points_[0]->force += force;
			for (auto spring : springs_) { spring->update(); };
			for (auto point : points_) { point->update(); };
			update();
		};
		virtual std::size_t getPointCount() const { return S; };

		// TODO: ベジェを利用して、曲線を描くようにする。
		// getPointCountでは S * ベジェの頂点数 を返せばおｋ
		virtual sf::Vector2f getPoint(std::size_t idx) const {
			return points_[idx]->position;
		};
	private:
		static const int DEFAULT_WEIGHT = 120;
		static const int CENTRER_WEIGHT = 99999;
		std::array<std::shared_ptr<Spring::Point>, S> points_;
		std::shared_ptr<Spring::Point> centerPoint_;
		std::array<std::shared_ptr<Spring>, S * 2> springs_;
	};
};