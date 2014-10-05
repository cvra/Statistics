#include <CppUTest/TestHarness.h>
#include <float.h>
#include <math.h>
#include "../statistics.h"

TEST_GROUP(StatisticsTest)
{
    statistics_t s;
    void setup(void)
    {
        statistics_reset(&s);
    }
};


TEST(StatisticsTest, CorrectNbSamples)
{
    CHECK_EQUAL(0, statistics_get_nb_samples(&s));
    statistics_add_sample(&s, 0);
    CHECK_EQUAL(1, statistics_get_nb_samples(&s));
    statistics_add_sample(&s, 0);
    CHECK_EQUAL(2, statistics_get_nb_samples(&s));
}

TEST(StatisticsTest, Min)
{
    statistics_add_sample(&s, 3);
    DOUBLES_EQUAL(3, statistics_get_min(&s), FLT_EPSILON);
    statistics_add_sample(&s, 5);
    DOUBLES_EQUAL(3, statistics_get_min(&s), FLT_EPSILON);
    statistics_add_sample(&s, -1);
    DOUBLES_EQUAL(-1, statistics_get_min(&s), FLT_EPSILON);
}

TEST(StatisticsTest, Max)
{
    statistics_add_sample(&s, 3);
    DOUBLES_EQUAL(3, statistics_get_max(&s), FLT_EPSILON);
    statistics_add_sample(&s, 2);
    DOUBLES_EQUAL(3, statistics_get_max(&s), FLT_EPSILON);
    statistics_add_sample(&s, 6);
    DOUBLES_EQUAL(6, statistics_get_max(&s), FLT_EPSILON);
}

TEST(StatisticsTest, Mean)
{
    statistics_add_sample(&s, 5);
    statistics_add_sample(&s, 10);
    statistics_add_sample(&s, 9);
    DOUBLES_EQUAL(8, statistics_get_mean(&s), FLT_EPSILON);
}

TEST(StatisticsTest, Variance)
{
    statistics_add_sample(&s, 5);
    statistics_add_sample(&s, 5);
    statistics_add_sample(&s, 10);
    statistics_add_sample(&s, 10);
    statistics_add_sample(&s, 9);
    statistics_add_sample(&s, 9);
    // (3^2+3^2+2^2+2^2+1^2+1^2)/5 = 5.6
    DOUBLES_EQUAL(5.6, statistics_get_var(&s), FLT_EPSILON);
}

TEST(StatisticsTest, StandardDeviation)
{
    statistics_add_sample(&s, 5);
    statistics_add_sample(&s, 5);
    statistics_add_sample(&s, 10);
    statistics_add_sample(&s, 10);
    statistics_add_sample(&s, 9);
    statistics_add_sample(&s, 9);
    DOUBLES_EQUAL(sqrt(5.6), statistics_get_stddev(&s), FLT_EPSILON);
}

TEST(StatisticsTest, VarianceZeroOrOneSample)
{
    DOUBLES_EQUAL(0, statistics_get_var(&s), FLT_EPSILON);
    statistics_add_sample(&s, 10);
    DOUBLES_EQUAL(0, statistics_get_var(&s), FLT_EPSILON);
}

TEST(StatisticsTest, ResetWorks)
{
    statistics_add_sample(&s, 5);
    statistics_add_sample(&s, 10);
    statistics_reset(&s);
    CHECK_EQUAL(0, statistics_get_nb_samples(&s));
    statistics_add_sample(&s, -1);
    DOUBLES_EQUAL(-1, statistics_get_min(&s), FLT_EPSILON);
    DOUBLES_EQUAL(-1, statistics_get_max(&s), FLT_EPSILON);
    DOUBLES_EQUAL(-1, statistics_get_mean(&s), FLT_EPSILON);
    statistics_add_sample(&s, 0);
    DOUBLES_EQUAL(0.5, statistics_get_var(&s), FLT_EPSILON);
}
