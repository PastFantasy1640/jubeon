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
	std::size_t pidx = idx / bezier_resolution_;	//�A�N�Z�X����point_[i]�̓_

	std::size_t pidxn = pidx + 1;					//�A�N�Z�X����point_[i+1]�̓_
	if (idxn == points_.size()) idxn = 0;

	std::size_t pidxnn = pidxn + 1;
	if (idxnn == points_.size()) idxnn = 0;


	//�J�n�_s
	sf::Vector s = (points_[pidx] + points_[pidxn]) / 2;

	//�I���_e
	sf::Vector e = (points_[pidxn] + points_[pidxnn]) / 2;

	//�R���g���[���|�C���gcp
	sf::Vector cp = points_[pidx];	//�Ⴄ�Ǝv���B

	sf::Vector2f v1 = cp - s;
	sf::Vector2f v2 = e - cp;

	float t = static_cast<float>(idx) / static_cast<float>(bezier_resolution_) - static_cast<float>(pidx);
	return (v1 * t + (v1 * (1 - t) + v2 * t) * t + s);

	
}*/

//template class Theme::Drop<5>;