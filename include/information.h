#pragma once
#include <vector>
#include "instruments.h"

namespace information
{
    // Forward declaration of Emitter
    struct Emitter;

    // Base class for news
    class News
    {
        long long int time;

    public:
         double sentiment;
        Emitter &emitter;

        News(double, Emitter &emitter, int time);
    };

    // Concrete news
    class SectorNews : public News
    {
    public:
        instruments::Sector* sector;

        SectorNews(double, Emitter &, int, instruments::Sector*);
    };

    class CompanyNews : public News
    {
    public:
        instruments::Company* company;

        CompanyNews(double, Emitter &emitter, int time, instruments::Company*);
    };

    // News stream
    struct NewsStream
    {
        std::vector<News> news;
    };

    // Emitter definition
    enum EmitterType
    {
        INFLUENCER,
        MEDIA_GROUP,
        OFFICIAL_EMITTER
    };

    struct Emitter
    {
    public:
        std::string name;
        double trustability;
        EmitterType type;

        Emitter(std::string, double, EmitterType);
        void emit(NewsStream &stream);
    };

}