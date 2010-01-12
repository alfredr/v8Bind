#ifndef V8BIND_EXCEPT_H_
#define V8BIND_EXCEPT_H_

#include <string>
#include <stdexcept>

namespace v8Bind {

    struct TypeCastFailureException : std::runtime_error {
        static const std::string Message;

        TypeCastFailureException() : 
            std::runtime_error(TypeCastFailureException::Message) { }
    };
    
    const std::string TypeCastFailureException::Message = "Type conversion failure";

    struct ConstCastFailureException : std::runtime_error {
        static const std::string Message;

        ConstCastFailureException()
            :std::runtime_error(ConstCastFailureException::Message) { }
    };
    
    const std::string ConstCastFailureException::Message = "Const cast failure";

    struct NullReferenceException : std::runtime_error {
        static const std::string Message;

        NullReferenceException() : 
            std::runtime_error(NullReferenceException::Message) { }
    };
    
    const std::string NullReferenceException::Message = "Holder is empty or missing.";

    struct InvalidOperationException : std::runtime_error {
        static const std::string Message;

        InvalidOperationException() : 
            std::runtime_error(InvalidOperationException::Message) { }
    };
    
    const std::string InvalidOperationException::Message = "Invalid operation";
  
    struct ArgumentCountException : std::runtime_error {
        static const std::string Message;

        ArgumentCountException() : 
            std::runtime_error(ArgumentCountException::Message) { }
    };
    
    const std::string ArgumentCountException::Message = "Incorrect argument count";


} // namespace v8Bind

#endif

