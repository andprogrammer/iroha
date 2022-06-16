/**
 * Copyright Soramitsu Co., Ltd. All Rights Reserved.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef IROHA_NETWORK_IMPL_HPP
#define IROHA_NETWORK_IMPL_HPP

#include "consensus/yac/transport/yac_network_interface.hpp"  // for YacNetwork
#include "yac.grpc.pb.h"

#include <memory>
#include <mutex>

#include "consensus/yac/vote_message.hpp"
#include "logger/logger_fwd.hpp"
#include "network/impl/client_factory.hpp"

namespace iroha::consensus::yac {
  /**
   * Class which provides implementation of client-side transport for
   * consensus based on grpc
   */
  class NetworkImpl : public YacNetwork {
   public:
    using Service = proto::Yac;
    using ClientFactory = iroha::network::ClientFactory<Service>;

    NetworkImpl(std::unique_ptr<iroha::network::ClientFactory<
                    ::iroha::consensus::yac::proto::Yac>> client_factory,
                logger::LoggerPtr log);

    void sendState(const shared_model::interface::Peer &to,
                   std::shared_ptr<proto::State> const &state) override;

    std::shared_ptr<proto::State> prepareYacState(const std::vector<VoteMessage> &state) override;

    void stop() override;

   private:
    /**
     * Yac stub creator
     */
    std::unique_ptr<ClientFactory> client_factory_;

    std::mutex stop_mutex_;
    bool stop_requested_{false};

    logger::LoggerPtr log_;
  };
}  // namespace iroha::consensus::yac

#endif  // IROHA_NETWORK_IMPL_HPP
