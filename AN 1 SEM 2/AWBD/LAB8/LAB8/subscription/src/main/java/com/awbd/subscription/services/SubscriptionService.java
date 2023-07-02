package com.awbd.subscription.services;

import com.awbd.subscription.model.Subscription;

import java.util.List;

public interface SubscriptionService {
    Subscription findByCoachAndSport(String coach, String sport);
    Subscription save(Subscription subscription);
    List<Subscription> findAll();
    Subscription delete(Long id);
    Subscription findById(Long id);
}
