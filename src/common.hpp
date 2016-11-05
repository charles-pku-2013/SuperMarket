#ifndef _COMMON_HPP_
#define _COMMON_HPP_

#include <string>
#include <sstream>
#include <memory>
#include <stdexcept>
#include <thread>
#include <chrono>


#define THIS_THREAD_ID        std::this_thread::get_id()
#define SLEEP_SECONDS(x)      std::this_thread::sleep_for(std::chrono::seconds(x))
#define SLEEP_MILLISECONDS(x) std::this_thread::sleep_for(std::chrono::milliseconds(x))
#define SPACES                " \t\f\r\v\n"

#define THROW_RUNTIME_ERROR(x) \
    do { \
        std::stringstream __err_stream; \
        __err_stream << x; \
        __err_stream.flush(); \
        throw std::runtime_error( __err_stream.str() ); \
    } while (0)

#define RET_MSG(args) \
    do { \
        std::stringstream __err_stream; \
        __err_stream << args; \
        __err_stream.flush(); \
        std::cerr << __err_stream.str() << std::endl; \
        return; \
    } while (0)

#define RET_MSG_VAL(val, args) \
    do { \
        std::stringstream __err_stream; \
        __err_stream << args; \
        __err_stream.flush(); \
        std::cerr << __err_stream.str() << std::endl; \
        return val; \
    } while (0)

#define COND_RET_MSG(cond, args) \
    do { \
        if (cond) RET_MSG(args); \
    } while (0)

#define COND_RET_MSG_VAL(cond, val, args) \
    do { \
        if (cond) RET_MSG_VAL(val, args); \
    } while (0)

#define ON_FINISH(name, deleter) \
    std::unique_ptr<void, std::function<void(void*)> > \
        name((void*)-1, [&](void*) deleter )

#define ON_FINISH_CLASS(name, deleter) \
    std::unique_ptr<void, std::function<void(void*)> > \
        name((void*)-1, [&, this](void*) deleter )

#define ON_FINISH_TYPE(type, name, ptr, deleter) \
    std::unique_ptr<type, std::function<void(type*)> > \
        name((ptr), [&](type* pArg) deleter )

#endif

