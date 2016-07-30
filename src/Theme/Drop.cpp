#include "Drop.hpp"

using namespace std;

/*
template<std::size_t S>
void Theme::Drop<S>::applyForce(sf::Vector2f force)
{
	points_[0]->force += force;
	for (auto spring : springs_) { spring->update(); };
	for (auto point : points_) { point->update(); };
	this->update();
}


template<std::size_t S>
std::size_t Theme::Drop<S>::getPointCount() const
{
	return S * bezier_resolution_;
}

template<std::size_t S>
sf::Vector2f Theme::Drop<S>::getPoint(std::size_t idx) const
{
	std::size_t pidx = idx / bezier_resolution_;	//アクセスするpoint_[i]の点

	std::size_t pidxn = pidx + 1;					//アクセスするpoint_[i+1]の点
	if (idxn == points_.size()) idxn = 0;

	std::size_t pidxnn = pidxn + 1;
	if (idxnn == points_.size()) idxnn = 0;


	//開始点s
	sf::Vector s = (points_[pidx] + points_[pidxn]) / 2;

	//終了点e
	sf::Vector e = (points_[pidxn] + points_[pidxnn]) / 2;

	//コントロールポイントcp
	sf::Vector cp = points_[pidx];	//違うと思う。

	sf::Vector2f v1 = cp - s;
	sf::Vector2f v2 = e - cp;

	float t = static_cast<float>(idx) / static_cast<float>(bezier_resolution_) - static_cast<float>(pidx);
	return (v1 * t + (v1 * (1 - t) + v2 * t) * t + s);

	
}*/

//template class Theme::Drop<5>;