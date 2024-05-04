#pragma once

template <unsigned int N>
class Filter
{
private:
    float samples[N];

public:
    Filter()
    {
        for (unsigned int x = 0; x < N; x++)
        {
            samples[x] = 0.0;
        }
    }
    float update(float sample)
    {

        // shift everything down
        for (unsigned int x = 0; x < N - 1; x++)
        {
            samples[x] = samples[x + 1];
        }
        // insert at the end
        samples[N - 1] = sample;
        // calculate new average
        float avg = 0.0;
        for (unsigned x = 0; x < N; x++)
        {
            avg += samples[x] / (float)N;
        }
        return avg;
    }
};