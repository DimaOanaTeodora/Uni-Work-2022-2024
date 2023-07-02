package com.awbd.subscription.controller;

import com.awbd.subscription.model.Discount;
import com.awbd.subscription.model.Subscription;
import com.awbd.subscription.services.DiscountServiceProxy;
import com.awbd.subscription.services.SubscriptionService;
import io.github.resilience4j.circuitbreaker.annotation.CircuitBreaker;
import io.swagger.v3.oas.annotations.Operation;
import io.swagger.v3.oas.annotations.media.Content;
import io.swagger.v3.oas.annotations.media.Schema;
import io.swagger.v3.oas.annotations.responses.ApiResponse;
import io.swagger.v3.oas.annotations.responses.ApiResponses;
import jakarta.validation.Valid;
import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.hateoas.CollectionModel;
import org.springframework.hateoas.Link;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.servlet.support.ServletUriComponentsBuilder;

import java.net.URI;
import java.util.List;


import static org.springframework.hateoas.server.mvc.WebMvcLinkBuilder.linkTo;
import static org.springframework.hateoas.server.mvc.WebMvcLinkBuilder.methodOn;


@RestController
@Slf4j
public class SubscriptionController {
    @Autowired
    DiscountServiceProxy discountServiceProxy;

    @Autowired
    SubscriptionService subscriptionService;


    @GetMapping(value = "/subscription/list", produces = {"application/hal+json"})
    public CollectionModel<Subscription> findAll() {

        List<Subscription> subscriptions = subscriptionService.findAll();
        for (final Subscription subscription : subscriptions) {
            Link selfLink = linkTo(methodOn(SubscriptionController.class).getSubscription(subscription.getId())).withSelfRel();
            subscription.add(selfLink);
            Link deleteLink = linkTo(methodOn(SubscriptionController.class).deleteSubscription(subscription.getId())).withRel("deleteSubscription");
            subscription.add(deleteLink);
        }
        Link link = linkTo(methodOn(SubscriptionController.class).findAll()).withSelfRel();
        CollectionModel<Subscription> result = CollectionModel.of(subscriptions, link);
        return result;
    }


    @GetMapping("/subscription/coach/{coach}/sport/{sport}")
    Subscription findByCoachAndSport(@PathVariable String coach,
                                     @PathVariable String sport){
        Subscription subscription = subscriptionService.findByCoachAndSport(coach, sport);


        Link selfLink = linkTo(methodOn(SubscriptionController.class).getSubscription(subscription.getId())).withSelfRel();

        subscription.add(selfLink);

        Discount discount = discountServiceProxy.findDiscount();
        log.info(discount.getVersionId());
        subscription.setPrice(subscription.getPrice()* (100 - discount.getMonth())/100);




        return subscription;
    }


    @PostMapping("/subscription")
    public ResponseEntity<Subscription> save(@Valid @RequestBody Subscription subscription){
        Subscription savedSubscription = subscriptionService.save(subscription);
        URI locationUri =ServletUriComponentsBuilder.fromCurrentRequest()
                .path("/{subscriptionId}").buildAndExpand(savedSubscription.getId())
                .toUri();

        return ResponseEntity.created(locationUri).body(savedSubscription);
    }


    @Operation(summary = "delete subscription by id")
    @ApiResponses(value = {
            @ApiResponse(responseCode = "200", description = "subscription deleted",
                    content = {@Content(mediaType = "application/json",
                            schema = @Schema(implementation = Subscription.class))}),
            @ApiResponse(responseCode = "400", description = "Invalid id",
                    content = @Content),
            @ApiResponse(responseCode = "404", description = "Subscription not found",
                    content = @Content)})
    @DeleteMapping("/subscription/{subscriptionId}")
    public Subscription deleteSubscription(@PathVariable Long subscriptionId) {

        Subscription subscription = subscriptionService.delete(subscriptionId);
        return subscription;
    }

    @GetMapping("/subscription/{subscriptionId}")
    @CircuitBreaker(name="discountById", fallbackMethod = "getSubscriptionFallback")
    public Subscription getSubscription(@PathVariable Long subscriptionId) {

        Subscription subscription = subscriptionService.findById(subscriptionId);
        Discount discount = discountServiceProxy.findDiscount();
        log.info(discount.getVersionId());
        subscription.setPrice(subscription.getPrice()* (100 - discount.getMonth())/100);
        return subscription;

    }

    private Subscription getSubscriptionFallback(Long subscriptionId, Throwable throwable) {

        Subscription subscription = subscriptionService.findById(subscriptionId);
        return subscription;
    }

}
