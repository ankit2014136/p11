#include "login_state_factory_impl.h"

#include "group_login_state.h"
#include "user_login_state.h"
#include "user_type.h"
#include <stdexcept>

namespace clicksharecertificateprovider
{
LoginStateFactoryImpl::LoginStateFactoryImpl(std::shared_ptr<Env> environment)
    : _environment(std::move(environment)) 
{
}

std::shared_ptr<LoginState>  LoginStateFactoryImpl::createLoginState(const UserType &userType) const
{
    switch (userType)
    {
    case UserType::SecurityOfficer:
        return std::make_shared<UserLoginState>(_environment);
    case UserType::User:
        return std::make_shared<GroupLoginState>(_environment);
    default:
        throw std::runtime_error("Unknown user type");
    }
}
} // namespace clicksharecertificateprovider