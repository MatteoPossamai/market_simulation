#include "instruments.h"
#include "information.h"
#include <vector>
#include <time.h>

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

    void Emitter::emit(NewsStream & stream, int time, instruments::Company* company, instruments::Sector* sector){
        int frequency = this->type == EmitterType::INFLUENCER ? 3 : this->type == EmitterType::MEDIA_GROUP ? 7 : 15;
        int publish = rand() % frequency;

        if (publish == 1){
          CompanyNews company_news = CompanyNews((double) rand()/RAND_MAX, *this, time, company);
          stream.add_news(company_news, time);
        }else if (publish == 2){
          SectorNews sector_news = SectorNews((double) rand()/RAND_MAX, *this, time, sector);
          stream.add_news(sector_news, time);
        }
    }

    void NewsStream::add_news(CompanyNews news, int time){
      this->news.push_back(news);
      if (!this->company_sentiment.count(*news.company)){
        this->company_sentiment[*news.company] = {};
      }
      this->company_sentiment.at(*news.company).push_back({time, news.sentiment});
    }

    void NewsStream::add_news(SectorNews news, int time){
      this->news.push_back(news);
      if (!this->sector_sentiment.count(*news.sector)){
        this->sector_sentiment[*news.sector] = {};
      }
      this->sector_sentiment.at(*news.sector).push_back({time, news.sentiment});
    }
}