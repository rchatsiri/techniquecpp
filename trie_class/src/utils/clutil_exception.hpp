#ifndef HNMAV_UTIL_CLUTIL_EXCEPTION_HPP
#define HNMAV_UTIL_CLUTIL_EXCEPTION_HPP

/* 						Titles														Authors 												Date
 * -Change to exception class for utility cl 		Chatsiri.rat										28/08/2012
 */  						

    class clutil_exception : public std::runtime_error
    {
        public:
            clutil_exception(cl_int err, const std::string& name)
                : std::runtime_error(add_msg_err(err, name)) {}

            std::string add_msg_err(cl_int err, const std::string& name);
    };



    std::string clutil_exception::add_msg_err(cl_int err, const std::string& name)
    {
        std::string error_msg("Error : ");
        error_msg.append(" ( ");
        error_msg.append(boost::lexical_cast<std::string>(err));
        error_msg.append(" ) ");
        return error_msg;
    }

#endif /* HNMAV_UTIL_CLUTIL_EXCEPTION_HPP */
