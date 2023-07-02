package com.awbd.lab4.domain;


import jakarta.persistence.EntityManager;
import org.junit.jupiter.api.Disabled;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.ValueSource;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.autoconfigure.jdbc.AutoConfigureTestDatabase;
import org.springframework.boot.test.autoconfigure.orm.jpa.DataJpaTest;
import org.springframework.test.annotation.Rollback;
import org.springframework.test.context.ActiveProfiles;

import java.util.Arrays;

@DataJpaTest
@ActiveProfiles("mysql")
@AutoConfigureTestDatabase(replace = AutoConfigureTestDatabase.Replace.NONE)
@Rollback(false)
public class CascadeTypesTest {

    @Autowired
    private EntityManager entityManager;

    @Test
    @Disabled
    public void saveParticipant() {
        Participant participant = new Participant();
        participant.setFirstName("Will");
        participant.setLastName("Snow");
        Product product = new Product();
        product.setName("Impression, Sunrise");
        product.setReservePrice(300D);
        product.setCode("PMON");
        product.setSeller(participant);
        participant.setProducts(Arrays.asList(product));
        entityManager.persist(participant);
    }


    @Test
    public void updateParticipant() {
        Product product = entityManager.find(Product.class, 2L);
        Participant participant = product.getSeller();
        participant.setFirstName("William");
        participant.getProducts().forEach(prod -> {
            prod.setCurrency(Currency.USD);
        });
        entityManager.merge(participant);


        entityManager.flush();
    }

    @Test
    public void orphanRemoval() {
        Product product = entityManager.find(Product.class, 1L);
        product.setInfo(null);
        entityManager.persist(product);
        entityManager.flush();
    }

    @ParameterizedTest
    @ValueSource(longs = {2, 3})
    public void orphanRemoval(long id) {
        Product product = entityManager.find(Product.class, id);
        product.setInfo(null);
        entityManager.persist(product);
        entityManager.flush();
    }


}
