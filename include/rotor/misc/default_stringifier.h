#pragma once

//
// Copyright (c) 2019-2024 Ivan Baidakou (basiliscos) (the dot dmol at gmail dot com)
//
// Distributed under the MIT Software License
//

#include "../messages.hpp"
#include "../message_stringifier.h"

#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable : 4251)
#endif

namespace rotor {

struct subscription_point_t;

namespace misc {

std::ostream &operator<<(std::ostream &, const subscription_point_t &);

struct ROTOR_API default_stringifier_t : message_stringifier_t,
                                       protected message_visitior_t,
                                       protected message::unsubscription_t::visitor_t,
                                       protected message::unsubscription_external_t::visitor_t,
                                       protected message::subscription_t::visitor_t,
                                       protected message::external_subscription_t::visitor_t,
                                       protected message::commit_unsubscription_t::visitor_t,
                                       protected message::handler_call_t::visitor_t,
                                       protected message::init_request_t::visitor_t,
                                       protected message::init_response_t::visitor_t,
                                       protected message::start_trigger_t::visitor_t,
                                       protected message::shutdown_trigger_t::visitor_t,
                                       protected message::shutdown_request_t::visitor_t,
                                       protected message::shutdown_response_t::visitor_t,
                                       protected message::create_actor_t::visitor_t,
                                       protected message::spawn_actor_t::visitor_t,
                                       protected message::registration_request_t::visitor_t,
                                       protected message::registration_response_t::visitor_t,
                                       protected message::deregistration_notify_t::visitor_t,
                                       protected message::deregistration_service_t::visitor_t,
                                       protected message::discovery_request_t::visitor_t,
                                       protected message::discovery_response_t::visitor_t,
                                       protected message::discovery_promise_t::visitor_t,
                                       protected message::discovery_future_t::visitor_t,
                                       protected message::discovery_cancel_t::visitor_t,
                                       protected message::link_request_t::visitor_t,
                                       protected message::link_response_t::visitor_t,
                                       protected message::unlink_notify_t::visitor_t,
                                       protected message::unlink_request_t::visitor_t,
                                       protected message::unlink_response_t::visitor_t {
    void stringify(std::stringstream &, const message_base_t &) const override;
    bool try_visit(const message_base_t &message) const override;

  protected:
    void on(const message::unsubscription_t &) override;
    void on(const message::unsubscription_external_t &) override;
    void on(const message::subscription_t &) override;
    void on(const message::external_subscription_t &) override;
    void on(const message::commit_unsubscription_t &) override;
    void on(const message::handler_call_t &) override;
    void on(const message::init_request_t &) override;
    void on(const message::init_response_t &) override;
    void on(const message::start_trigger_t &) override;
    void on(const message::shutdown_trigger_t &) override;
    void on(const message::shutdown_request_t &) override;
    void on(const message::shutdown_response_t &) override;
    void on(const message::create_actor_t &) override;
    void on(const message::spawn_actor_t &) override;
    void on(const message::registration_request_t &) override;
    void on(const message::registration_response_t &) override;
    void on(const message::deregistration_notify_t &) override;
    void on(const message::deregistration_service_t &) override;
    void on(const message::discovery_request_t &) override;
    void on(const message::discovery_response_t &) override;
    void on(const message::discovery_promise_t &) override;
    void on(const message::discovery_future_t &) override;
    void on(const message::discovery_cancel_t &) override;
    void on(const message::link_request_t &) override;
    void on(const message::link_response_t &) override;
    void on(const message::unlink_notify_t &) override;
    void on(const message::unlink_request_t &) override;
    void on(const message::unlink_response_t &) override;

    mutable std::stringstream *stream = nullptr;
};

} // namespace misc
} // namespace rotor

#if defined(_MSC_VER)
#pragma warning(pop)
#endif
