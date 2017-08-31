﻿#include "word.hpp"

namespace Flounder
{
	word::word() :
		m_characters(new std::vector<character*>()),
		m_width(0.0)
	{
	}

	word::~word()
	{
		delete m_characters;
	}

	bool word::addCharacter(character *c)
	{
		if (c == nullptr)
		{
			return false;
		}

		m_characters->push_back(c);
		m_width += c->getAdvanceX();
		return true;
	}
}