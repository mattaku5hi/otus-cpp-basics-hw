#include <cmath>
#include <iostream>
#include <memory>

#include "statistics.hpp"


Min::Min() :
	m_min{std::numeric_limits<double>::max()}
{

}

void Min::update(double next)
{
	if(next < this->m_min)
	{
		m_min = next;
	}

	return;
}

double Min::eval() const
{
	return this->m_min;
}

const char* Min::name() const
{
	return "min";
}


Max::Max() :
	m_max{std::numeric_limits<double>::lowest()}
{

}

void Max::update(double next)
{
	if(next > this->m_max)
	{
		m_max = next;
	}

	return;
}

double Max::eval() const
{
	return this->m_max;
}

const char* Max::name() const
{
	return "max";
}


Mean::Mean() :
	m_amount{0}, m_sum{0.0}, m_mean{0.0}
{

}

void Mean::update(double next)
{
	m_amount++;
	m_sum += next;
	m_mean = m_sum / static_cast<double>(m_amount);

	return;
}

double Mean::eval() const
{
	return this->m_amount > 0 ? this->m_mean : 0.0;
}

const char* Mean::name() const
{
	return "mean";
}


Std::Std() :
	m_amount{0}, m_sum{0.0}, m_mean{0.0}, m_sumSquared{0.0}, m_std{0.0}
{

}

void Std::update(double next)
{
	m_amount++;
	m_sum += next;
	m_sumSquared += next * next;
	m_mean = m_sum / static_cast<double>(m_amount);

	return;
}

double Std::eval() const
{
	/* STD is undefined for one number */
	if(m_amount < 2)
	{
		return 0.0;
	}

	double variance = (m_sumSquared - m_amount * m_mean * m_mean) / m_amount;
	return std::sqrt(variance);
}

const char* Std::name() const
{
	return "std";
}


Pct::Pct(unsigned int percentage) :
	m_percentage{percentage}, m_index{0},
	m_pctDesc{"pct" + std::to_string(percentage)}
{

}

void Pct::update(double next)
{
	if(m_values.size() == 0)
	{
		m_values.push_back(next);
		return;
	}

	/* Insert incoming value so that container remains sorted by increasing */
	auto it = std::lower_bound(m_values.begin(), m_values.end(), next);
	m_values.insert(it, next);
	
	/* Actualize percentile */
	std::size_t amount = m_values.size();
	double index = static_cast<double>((static_cast<double>(m_percentage / 100.0)) * amount - 1.0);
	m_index = std::ceil(index);

	return;
}

double Pct::eval() const
{
	/* Percentile is undefined for one number */
	if(m_values.size() < 2)
	{
		return 0.0;
	}

	return m_values[m_index];
}

const char* Pct::name() const
{
	return m_pctDesc.c_str();
}



int main()
{
	int status{EXIT_SUCCESS};
	double value;
	std::vector<std::unique_ptr<IStatistics>> statistics;

	statistics.push_back(std::make_unique<Min>());
	statistics.push_back(std::make_unique<Max>());
	statistics.push_back(std::make_unique<Mean>());
	statistics.push_back(std::make_unique<Std>());
	statistics.push_back(std::make_unique<Pct>(90));
	statistics.push_back(std::make_unique<Pct>(95));

	while(std::cin >> value)
	{
		for(auto& stat : statistics)
		{
			stat->update(value);
		}
	}
	if(std::cin.eof() == true)
	{
		std::cout << std::endl;
		for(auto& stat : statistics)
		{
			std::cout << stat->name() << " = " << stat->eval() << std::endl;
		}
	}
	else if(std::cin.fail())
	{
		std::cerr << "Invalid value has been received\n";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		status = EXIT_FAILURE;
	}

	/* Explicit */
	statistics.clear();
	return status;
}