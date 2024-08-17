#include "instruments.h"
#include "information.h"
#include <vector>

namespace information
{
    News::News(double sentiment_value, Emitter &emitter, int time_value)
        : sentiment(sentiment_value),
          emitter(emitter),
          time(time_value) {}

    SectorNews::SectorNews(double sentiment_value, Emitter &emitter, int time_value, instruments::Sector* sector_value)
        : News(sentiment_value, emitter, time_value),
          sector(sector_value) {}

    CompanyNews::CompanyNews(double sentiment_value, Emitter &emitter, int time_value, instruments::Company* company_value)
        : News(sentiment_value, emitter, time_value),
          company(company_value) {}

    Emitter::Emitter(std::string name_value, double trustability_value, EmitterType type_value)
        : name(name_value),
          trustability(trustability_value),
          type(type_value) {}

    void Emitter::emit(NewsStream & stream){
        // TODO: decide how to rotate the news creation and such 
    }
}