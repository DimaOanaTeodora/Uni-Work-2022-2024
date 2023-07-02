package com.awbd.subscription.repositories;

import com.awbd.subscription.model.Subscription;
import org.springframework.data.repository.CrudRepository;

public interface SubscriptionRepository extends CrudRepository<Subscription, Long> {
    Subscription findByCoachAndSport(String coach, String sport);
}
