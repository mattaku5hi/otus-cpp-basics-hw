#ifndef STATISTICS_HPP
#define STATISTICS_HPP

#include <limits>
#include <vector>


class IStatistics
{
public:
	virtual ~IStatistics() {}

	virtual void update(double next) = 0;
	virtual double eval() const = 0;
	virtual const char * name() const = 0;
};

class Min : public IStatistics
{
private:
	double m_min;

public:
	Min(void);

	void update(double next) override;
	double eval() const override;
	const char * name() const override;
};

class Max : public IStatistics
{
private:
	double m_max;

public:
	Max(void);

	void update(double next) override;
	double eval() const override;
	const char * name() const override;
};

class Mean : public IStatistics
{
private:
    unsigned int m_amount;
    double m_sum;
	double m_mean;

public:
	Mean(void);

	void update(double next) override;
	double eval() const override;
	const char * name() const override;
};

class Std : public IStatistics
{
private:
    unsigned int m_amount;
    double m_sum;
	double m_mean;
    double m_sumSquared;
	double m_std;

public:
	Std(void);

	void update(double next) override;
	double eval() const override;
	const char * name() const override;
};

class Pct : public IStatistics
{
private:
    const unsigned int m_percentage;
    unsigned int m_index;
    const std::string m_pctDesc;
    std::vector<double> m_values;

public:
	Pct(unsigned int percentage);

	void update(double next) override;
	double eval() const override;
	const char * name() const override;
};


#endif // STATISTICS_HPP
