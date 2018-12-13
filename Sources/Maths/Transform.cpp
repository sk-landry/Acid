﻿#include "Transform.hpp"

#include "Network/Packet.hpp"
#include "Serialized/Metadata.hpp"
#include "Quaternion.hpp"

namespace acid
{
	const Transform Transform::ZERO = Transform(Vector3::ZERO, Vector3::ZERO, Vector3::ONE);

	Transform::Transform() :
		m_position(Vector3()),
		m_rotation(Vector3()),
		m_scaling(Vector3(1.0f, 1.0f, 1.0f))
	{
	}

	Transform::Transform(const Transform &source) :
		m_position(source.m_position),
		m_rotation(source.m_rotation),
		m_scaling(source.m_scaling)
	{
	}

	Transform::Transform(const Vector3 &position, const Vector3 &rotation, const Vector3 &scaling) :
		m_position(position),
		m_rotation(rotation),
		m_scaling(scaling)
	{
	}

	Transform::Transform(const Vector3 &position, const Vector3 &rotation, const float &scale) :
		m_position(position),
		m_rotation(rotation),
		m_scaling(Vector3(scale, scale, scale))
	{
	}

	Transform Transform::Multiply(const Transform &other) const
	{
		return Transform(m_position + (m_position.ToQuaternion() * other.m_position), m_rotation + other.m_rotation, m_scaling * other.m_scaling); // TODO: Create method.
	}

	Matrix4 Transform::GetWorldMatrix() const
	{
		return Matrix4::TransformationMatrix(m_position, m_rotation, m_scaling);
	}

	Matrix4 Transform::GetModelMatrix() const
	{
		return Matrix4::TransformationMatrix(Vector3::ZERO, m_rotation, Vector3::ZERO);
	}

	void Transform::Decode(const Metadata &metadata)
	{
		m_position = metadata.GetChild<Vector3>("Position");
		m_rotation = metadata.GetChild<Vector3>("Rotation");
		m_scaling = metadata.GetChild<Vector3>("Scaling");
	}

	void Transform::Encode(Metadata &metadata) const
	{
		metadata.SetChild<Vector3>("Position", m_position);
		metadata.SetChild<Vector3>("Rotation", m_rotation);
		metadata.SetChild<Vector3>("Scaling", m_scaling);
	}

	bool Transform::operator==(const Transform &other) const
	{
		return m_position == other.m_position && m_rotation == other.m_rotation && m_scaling == other.m_scaling;
	}

	bool Transform::operator!=(const Transform &other) const
	{
		return !(*this == other);
	}

	Transform operator*(const Transform &left, const Transform &right)
	{
		return left.Multiply(right);
	}

	Transform &Transform::operator*=(const Transform &other)
	{
		return *this = Multiply(other);
	}

	std::ostream &operator<<(std::ostream &stream, const Transform &transform)
	{
		stream << transform.ToString();
		return stream;
	}

	Packet &operator<<(Packet &packet, const Transform &transform)
	{
		return packet << transform.m_position << transform.m_rotation << transform.m_scaling;
	}

	Packet &operator>>(Packet &packet, Transform &transform)
	{
		return packet >> transform.m_position >> transform.m_rotation >> transform.m_scaling;
	}

	std::string Transform::ToString() const
	{
		std::stringstream result;
		result << "Transform(" << m_position << ", " << m_rotation << ", " << m_scaling << ")";
		return result.str();
	}
}
