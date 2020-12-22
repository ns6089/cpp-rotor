#pragma once

//
// Copyright (c) 2019-2020 Ivan Baidakou (basiliscos) (the dot dmol at gmail dot com)
//
// Distributed under the MIT Software License
//

#include "address.hpp"
#include "message.h"
#include "state.h"
#include "request.hpp"
#include "subscription_point.h"
#include "forward.hpp"

namespace rotor {

/// namespace for rotor core payloads
namespace payload {

/** \struct initialize_confirmation_t
 *  \brief Message with this payload is sent from an actor to its supervisor to
 * confirm successful initialization
 */
struct initialize_confirmation_t {};

/** \struct initialize_actor_t
 *  \brief Message with this payload is sent from a supervisor to an actor as
 *  initialization request
 */
struct initialize_actor_t {
    /** \brief link to response payload type */
    using response_t = initialize_confirmation_t;
};

/** \struct start_actor_t
 *  \brief Message with this payload is sent from a supervisor to an actor as
 *  start confirmation
 */
struct start_actor_t {};

/** \struct create_actor_t
 *  \brief Message with this payload is sent to supervisor when an actor is
 * created (constructed).
 *
 * The message is needed for internal {@link supervisor_t} housekeeping.
 *
 */
struct create_actor_t {
    /** \brief the intrusive pointer to created actor */
    actor_ptr_t actor;

    /** \brief maximum time for actor initialization
     *
     * If an actor isn't able to confirm initialization in time, it
     * will be asked to shutdown (default behavior)
     *
     */
    pt::time_duration timeout;
};

/** \struct shutdown_trigger_t
 *  \brief Message with this payload is sent to ask an actor's supervisor
 * to initate shutdown procedure.
 *
 */
struct shutdown_trigger_t {
    /** \brief the actor to be shut down */
    address_ptr_t actor_address;
};

/** \struct shutdown_confirmation_t
 *  \brief Message with this payload is sent from an actor to its supervisor to
 * confirm successful shutdown.
 */
struct shutdown_confirmation_t {};

/** \struct shutdown_request_t
 *  \brief Message with this payload is sent from a supervisor to an actor as
 *  shutdown request
 */
struct shutdown_request_t {
    /** \brief link to response payload type */
    using response_t = shutdown_confirmation_t;
};

/** \struct handler_call_t
 *  \brief Message with this payload is forwarded to the handler's supervisor for
 * the delivery of the original message.
 *
 * An `address` in `rotor` is always generated by a supervisor. All messages to the
 * address are initially pre-processed by the supervisor: if the destination handler
 * supervisor is the same as the message address supervisor, the handler is invoked
 * immediately. Otherwise, if a handler belongs to different supervisor (i.e. may
 * be to different event loop), then the delivery of the message is forwarded to
 * that supersior.
 *
 */
struct handler_call_t {
    /** \brief The original message (intrusive pointer) sent to an address */
    message_ptr_t orig_message;

    /** \brief The handler (intrusive pointer) on some external supervisor,
     * which can process the original message */
    handler_ptr_t handler;
};

/** \struct external_subscription_t
 *  \brief Message with this payload is forwarded to the target address supervisor
 * for recording subscription in the external (foreign) handler
 *
 * When a supervisor process subscription requests from it's (local) actors, it
 * can found that the `target_address` belongs to some other (external/foreign)
 * supervisor. In that case the subscription is forwarded to the external
 * supervisor.
 *
 */
struct external_subscription_t {
    /** \brief subscription details */
    subscription_point_t point;
};

/** \struct subscription_confirmation_t
 *  \brief Message with this payload is sent from a supervisor to an actor when
 *  successfull subscription to the `target` address occurs.
 *
 * The message is needed for internal {@link actor_base_t} housekeeping.
 *
 */
struct subscription_confirmation_t {
    /** \brief subscription details */
    subscription_point_t point;
};

/** \struct external_unsubscription_t
 *  \brief Message with this payload is forwarded to the target address supervisor
 * for recording unsubscription in the external (foreign) handler.
 *
 * The message is symmetrical to the {@link external_subscription_t}.
 *
 */
struct external_unsubscription_t {
    /** \brief subscription details */
    subscription_point_t point;
};

/** \struct commit_unsubscription_t
 *  \brief Message with this payload is sent to the target address supervisor
 * for confirming unsubscription in the external (foreign) handler.
 *
 * The message is an actor-reply to {@link external_subscription_t} request.
 *
 */
struct commit_unsubscription_t {
    /** \brief subscription details */
    subscription_point_t point;
};

/** \struct unsubscription_confirmation_t
 *  \brief Message with this payload is sent from a supervisor to an actor with
 *  confirmation that `pooint` is no longer active (subscribed).`
 */
struct unsubscription_confirmation_t {
    /** \brief subscription details */
    subscription_point_t point;
};

/** \struct registration_response_t
 *  \brief Successful registraction response (no content)
 */
struct registration_response_t {};

/** \struct registration_request_t
 *  \brief "name - >service address mapping" request
 */
struct registration_request_t {
    /** \brief link to registration response payload type */
    using response_t = registration_response_t;

    /** \brief (unique) name of the sevice address in the registry */
    std::string service_name;

    /** \brief actual service address */
    address_ptr_t service_addr;
};

/** \struct deregistration_notify_t
 *  \brief deregistration notification for all names associated
 *  with service address
 */
struct deregistration_notify_t {
    /** \brief service address for deregistration */
    address_ptr_t service_addr;
};

/** \struct deregistration_service_t
 *  \brief removes single service by name from a registry
 */
struct deregistration_service_t {
    /** \brief the  name of the sevice address to be removed for a registry */
    std::string service_name;
};

/** \struct discovery_reply_t
 *  \brief successful result of service discovery
 */
struct discovery_reply_t {
    /**  \brief the service address found by name in a registry */
    address_ptr_t service_addr;
};

/** \struct discovery_request_t
 *  \brief discover service by name in a registry
 */
struct discovery_request_t {
    /** \brief link to discovery response payload type */
    using response_t = discovery_reply_t;

    /**  \brief the service name to be looked in a registry */
    std::string service_name;
};

/** \struct discovery_future_t
 *  \brief delayed discovery response as soon as an address has been registered
 */
struct discovery_future_t {
    /**  \brief the service address found by name in a registry */
    address_ptr_t service_addr;
};

/** \struct discovery_promise_t
 *  \brief ask registry for {@link discovery_future_t} when the target
 *  service name has been registered
 */
struct discovery_promise_t {
    /** \brief link to discovery future payload type */
    using response_t = discovery_future_t;
    /**  \brief the service name to be looked in a registry */
    std::string service_name;
};

/** \struct link_response_t
 *  \brief successful confirmation to {@link link_request_t}
 */
struct link_response_t {};

/** \struct link_request_t
 *  \brief requests target actor to be linked with the current one
 */
struct link_request_t {
    /** \brief link to link response payload type */
    using response_t = link_response_t;

    /** \brief wait until target server (actor) starts, only then reply to the source actor */
    bool operational_only;
};

/** \struct unlink_notify_t
 * \brief "client" notifies "server" that the connection has been closed
 * from its side
 */
struct unlink_notify_t {
    /** \brief client actor address in unlinking */
    address_ptr_t client_addr;
};

/** \struct unlink_request_t
 *  \brief "server" asks "client" for closing connection
 */
struct unlink_request_t {
    /** \brief link to unlink response payload type */
    using response_t = unlink_notify_t;

    /** \brief server actor address in unlinking */
    address_ptr_t server_addr;
};

} // namespace payload

/// namespace for rotor core messages (which just transform payloads)
namespace message {

// subscription-related
/** \brief unsubscription confirmation message */
using unsubscription_t = message_t<payload::unsubscription_confirmation_t>;
/** \brief external unsubscription message */
using unsubscription_external_t = message_t<payload::external_unsubscription_t>;
/** \brief subscription confirmation message */
using subscription_t = message_t<payload::subscription_confirmation_t>;

/** \brief external subscription message */
using external_subscription_t = message_t<payload::external_subscription_t>;
/** \brief unsubscription commit message */
using commit_unsubscription_t = message_t<payload::commit_unsubscription_t>;

/** \brief delivers foreign message to the actor's supervisor
 *
 * Unpon delivery the appropriate handler on the actor will be thread-safely
 * called by it's supervisor
 */
using handler_call_t = message_t<payload::handler_call_t>;

// lifetime-related
/** \brief actor initialization request */
using init_request_t = request_traits_t<payload::initialize_actor_t>::request::message_t;
/** \brief actor initialization response */
using init_response_t = request_traits_t<payload::initialize_actor_t>::response::message_t;

/** \brief actor start trigger */
using start_trigger_t = message_t<payload::start_actor_t>;

/** \brief actor shutdown trigger */
using shutdown_trigger_t = message_t<payload::shutdown_trigger_t>;
/** \brief actor shutdown request */
using shutdown_request_t = request_traits_t<payload::shutdown_request_t>::request::message_t;
/** \brief actor shutdown response */
using shutdown_response_t = request_traits_t<payload::shutdown_request_t>::response::message_t;

/** \brief supervisor's message upon actor instantiation */
using create_actor_t = message_t<payload::create_actor_t>;

// registry-related
/** \brief name/address registration request */
using registration_request_t = request_traits_t<payload::registration_request_t>::request::message_t;
/** \brief name/address registration response */
using registration_response_t = request_traits_t<payload::registration_request_t>::response::message_t;
/** \brief deregistration notification (from client) */
using deregistration_notify_t = message_t<payload::deregistration_notify_t>;
/** \brief deregistration notification (from registry-server) */
using deregistration_service_t = message_t<payload::deregistration_service_t>;

/** \brief name discovery request */
using discovery_request_t = request_traits_t<payload::discovery_request_t>::request::message_t;
/** \brief name discovery response */
using discovery_response_t = request_traits_t<payload::discovery_request_t>::response::message_t;
/** \brief name discovery promise (aka get response when name will be available) */
using discovery_promise_t = request_traits_t<payload::discovery_promise_t>::request::message_t;
/** \brief name discovery future (reply to promise) */
using discovery_future_t = request_traits_t<payload::discovery_promise_t>::response::message_t;
/** \brief name discovery promise cancellation */
using discovery_cancel_t = request_traits_t<payload::discovery_promise_t>::cancel::message_t;

// link-related
/** \brief actor link request */
using link_request_t = request_traits_t<payload::link_request_t>::request::message_t;
/** \brief actor link response */
using link_response_t = request_traits_t<payload::link_request_t>::response::message_t;
/** \brief unlink notification (client is no longer interested in the link) */
using unlink_notify_t = message_t<payload::unlink_notify_t>;
/** \brief unlink request (server is asking client to cancel link) */
using unlink_request_t = request_traits_t<payload::unlink_request_t>::request::message_t;
/** \brief unlink response (client confirms link cancellation) */
using unlink_response_t = request_traits_t<payload::unlink_request_t>::response::message_t;

} // namespace message

} // namespace rotor
