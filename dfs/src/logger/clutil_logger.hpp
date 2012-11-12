#ifndef HNMAV_UTIL_CLUTIL_LOGGER_HPP
#define HNMAV_UTIL_CLUTIL_LOGGER_HPP

/*-Titles                                                   Authors                 Date
 *-Init Class logging for project ( Logging version not includes log level.)
 *                                                          Chatsiri.rat            26/02/2012
 *-Add shared ptr for handling log	( unthreadsafe )        Cahtsiri.rat            04/10/2012
 */

#include <iostream>
#include <string>

#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

#include <boost/log/common.hpp>
#include <boost/log/formatters.hpp>
#include <boost/log/filters.hpp>
#include <boost/log/attributes/timer.hpp>

#include <boost/log/utility/init/to_file.hpp>
#include <boost/log/utility/init/to_console.hpp>
#include <boost/log/utility/init/common_attributes.hpp>
#include <boost/log/utility/init/from_stream.hpp>

#include <boost/log/sinks/sync_frontend.hpp>
#include <boost/log/sinks/text_multifile_backend.hpp>
#include <boost/log/sinks/syslog_backend.hpp>

#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <boost/thread/locks.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread.hpp>

namespace  hnmav_util
{
    namespace logging = boost::log;
    namespace fmt			= boost::log::formatters;
    namespace flt 		= boost::log::filters;
    namespace sinks		= boost::log::sinks;
    namespace attrs		= boost::log::attributes;
    namespace src			= boost::log::sources;
    namespace keywords = boost::log::keywords;
    using namespace boost;

    enum severity_level {
        normal,
        warning,
        error
    };


    BOOST_LOG_DECLARE_GLOBAL_LOGGER(write_log,src::logger_mt)

    template<typename CONT = std::string,  typename CONT1 =  int  >
    class clutil_logging
    {
        public:
            void init_backend();
            void init_frontend();

            void formatter_normal();
            void formatter_error();

            void write_info(CONT const& write_info);
            void write_info(CONT const& write_detail, CONT const& write_info);
            void write_error(CONT const& write_error);
            void write_warning(CONT const& write_warning);

            static shared_ptr<clutil_logging<CONT, CONT1> >& get_instance();
            void add_logger(CONT const&);
            void add_settings(CONT const&);


            ~clutil_logging();


        private:
            CONT  file_path_;
            CONT1 log_level_;
            bool isInt_;

            static shared_ptr<clutil_logging<CONT, CONT1> >   *logging_instance;

            clutil_logging();
            clutil_logging& operator=(const clutil_logging& logging);
            clutil_logging(const clutil_logging& logging);

            // back end
            typedef sinks::synchronous_sink< sinks::text_multifile_backend >  file_sink;
            typedef shared_ptr<sinks::synchronous_sink< sinks::text_multifile_backend> >  file_sink_ptr;
            std::vector<shared_ptr<sinks::synchronous_sink< sinks::text_multifile_backend> > >  sinks_vec;

            // front end
            typedef shared_ptr<logging::core>   core_ptr;
            std::vector<shared_ptr<logging::core> > frontend_core_vec;

            std::vector<std::string> logger_file_path;
            std::string logger_settings_path;

    };

    template<typename CONT, typename CONT1>
    shared_ptr<clutil_logging<CONT, CONT1> > *clutil_logging<CONT, CONT1>::logging_instance = NULL;


    template<typename CONT, typename CONT1>
    void clutil_logging<CONT, CONT1>::add_logger(CONT const&  logger_file)
    {
        logger_file_path.push_back(logger_file);
    }

    template<typename CONT, typename CONT1>
    void clutil_logging<CONT, CONT1>::add_settings(CONT const& logger_settings_file)
    {
        logger_settings_path = logger_settings_file;
    }

    template<typename CONT, typename CONT1>
    shared_ptr<clutil_logging<CONT, CONT1> >& clutil_logging<CONT, CONT1>::get_instance()
    {

        if(logging_instance == NULL)
            logging_instance = new shared_ptr<clutil_logging<CONT, CONT1> >(new clutil_logging<CONT, CONT1>());

        return  *logging_instance;

    }
    template<typename CONT, typename CONT1>
    clutil_logging<CONT, CONT1>::clutil_logging()
    {
        //backend
    }

    template<typename CONT, typename CONT1>
    clutil_logging<CONT, CONT1>::~clutil_logging()
    {
        for(std::vector<shared_ptr<sinks::synchronous_sink< sinks::text_multifile_backend> > >::iterator iter = sinks_vec.begin();
                iter != sinks_vec.end();
                ++iter) {
            shared_ptr<sinks::synchronous_sink< sinks::text_multifile_backend> > syn_sinks_ptr = *iter;
            syn_sinks_ptr.reset();
        }
    }

    template<typename CONT, typename CONT1>
    void clutil_logging<CONT, CONT1>::write_info(CONT  const& write_info)
    {
        BOOST_LOG(write_log::get())<< write_info;
    }

    template<typename CONT, typename CONT1>
    void clutil_logging<CONT, CONT1>::write_info(CONT  const& write_detail, CONT const& write_info)
    {
        BOOST_LOG(write_log::get())<< write_detail <<" : "<<  write_info;
    }

    template<typename CONT, typename CONT1>
    void clutil_logging<CONT, CONT1>::write_warning(CONT const& write_warning)
    {
        BOOST_LOG(write_log::get())<< write_warning;
    }

    template<typename CONT, typename CONT1>
    void clutil_logging<CONT, CONT1>::write_error(CONT const& write_error)
    {
        BOOST_LOG(write_log::get())<< write_error;
    }

    template<typename CONT, typename CONT1>
    void clutil_logging<CONT, CONT1>::formatter_normal()
    {
        file_sink_ptr sinks_ptr = sinks_vec.back();

        sinks_ptr->locked_backend()->set_formatter(
                fmt::format("%1%:- [%2%] :- %3% ")
                % fmt::attr< unsigned int >("Line #")
                % fmt::date_time< boost::posix_time::ptime >("TimeStamp")
                % fmt::message()
        );

    }
    template<typename CONT, typename CONT1>
    void clutil_logging<CONT, CONT1>::formatter_error()
    {
        file_sink_ptr sinks_ptr = sinks_vec.back();

        sinks_ptr->locked_backend()->set_formatter(
                fmt::format("%1%:- [%2%] Error :- %3% ")
                % fmt::attr< unsigned int >("Line #")
                % fmt::date_time< boost::posix_time::ptime >("TimeStamp")
                % fmt::message()
        );

    }


    template<typename CONT, typename CONT1>
    void clutil_logging<CONT, CONT1>::init_backend()
    {
        std::cout<<" Init logging backend()..." <<std::endl;
        file_sink_ptr sinks_ptr  = shared_ptr<sinks::synchronous_sink
                < sinks::text_multifile_backend> >(new file_sink);

        for(std::vector<std::string>::iterator  iter = logger_file_path.begin();
                iter != logger_file_path.end();
                ++iter) {
            sinks_ptr->locked_backend()->set_file_name_composer(
                    fmt::stream<< *iter << ".log");
            std::cout<<" logger path = " << *iter <<std::endl;
        }

        sinks_vec.push_back(sinks_ptr);


    }

    template<typename CONT, typename CONT1>
    void clutil_logging<CONT, CONT1>::init_frontend()
    {
        std::cout<<" Init logging frontend()..." <<std::endl;
        core_ptr core = logging::core::get();
        core->get()->add_sink(sinks_vec.back());

        // Add some attributes too
        shared_ptr< logging::attribute > attr(new attrs::local_clock);
        core->get()->add_global_attribute("TimeStamp", attr);
        attr.reset(new attrs::counter< unsigned int >);
        core->get()->add_global_attribute("Line #", attr);


        frontend_core_vec.push_back(core);
    }


}

#endif /* HNMAV_UTIL_CLUTIL_LOGGER_HPP */



