#pragma once
#include <cmath>
#include <vector>
#include <memory>
#include <functional>
#include "SFML/Graphics.hpp"
namespace Theme {

	class Spring {
	public:
		typedef struct Point {
			sf::Vector2f position;
			sf::Vector2f force;
			sf::Vector2f acceleration;
			sf::Vector2f speed;
			int weight;
			std::vector<std::shared_ptr<Spring>> springs;

			Point()
				: position(0, 0),
				force(0, 0),
				acceleration(0, 0),
				speed(0, 0),
				weight(0) {};

			inline void update() {
				acceleration = force;
				acceleration *= (1.0f / weight);
				speed += acceleration;
				position += speed;
				acceleration = sf::Vector2f(0, 0);
				force = sf::Vector2f(0, 0);
			};

			inline void connectSpring(std::shared_ptr<Spring> spring) {
				springs.push_back(spring);
			};
		} Point;
		Spring()
			: springConst_(0.5),
			startPoint_(nullptr),
			endPoint_(nullptr),
			powOfSpring_(sf::Vector2f(0, 0)) {};
		Spring(float springConst, std::shared_ptr<Point> start, std::shared_ptr<Point> end)
			: springConst_(springConst),
			startPoint_(start),
			endPoint_(end),
			powOfSpring_(sf::Vector2f(0, 0)) {
			init();
		};

		inline void init() {
			auto diffVec = endPoint_->position - startPoint_->position;
			originDistance_ = std::sqrt(pow(diffVec.x, 2) + pow(diffVec.y, 2));
		};
		inline std::shared_ptr<Point> getStartPoint() { return startPoint_; };
		inline std::shared_ptr<Point> getEndPoint() { return startPoint_; };
		inline void update() {
			auto diffVec = endPoint_->position - startPoint_->position;
			float distance = std::sqrt(pow(diffVec.x, 2) + pow(diffVec.y, 2));
			float ratio = originDistance_ / distance;

			// ƒoƒl‚Ì”½”­—Í‚ðŒvŽZ
			auto changeVec = diffVec - diffVec * ratio;
			powOfSpring_ = changeVec * (0 - springConst_);
			auto powOfSource = powOfSpring_ * -1.0f;
			startPoint_->force += powOfSource;
			endPoint_->force += powOfSpring_;
		};
	private:
		float originDistance_;
		float springConst_;
		sf::Vector2f powOfSpring_;
		std::shared_ptr<Point> startPoint_;
		std::shared_ptr<Point> endPoint_;
	};

};