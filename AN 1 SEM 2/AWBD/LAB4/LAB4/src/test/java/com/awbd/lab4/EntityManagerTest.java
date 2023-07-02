package com.awbd.lab4;

import com.awbd.lab4.domain.Currency;
import com.awbd.lab4.domain.Product;
import jakarta.persistence.EntityManager;
import org.junit.jupiter.api.Test;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.autoconfigure.orm.jpa.DataJpaTest;
import org.springframework.test.context.ActiveProfiles;

import static org.junit.jupiter.api.Assertions.assertEquals;


@DataJpaTest
@ActiveProfiles("h2")
public class EntityManagerTest {

    @Autowired
    private EntityManager entityManager;

    @Test
    public void findProduct() {

        Product productFound = entityManager.find(Product.class, 1L);

        assertEquals(productFound.getCode(), "PCEZ");
    }

    @Test
    public void updateProduct() {

        Product productFound = entityManager.find(Product.class, 1L);
        productFound.setCurrency(Currency.EUR);

        entityManager.persist(productFound);

        productFound = entityManager.find(Product.class, 1L);
        assertEquals(Currency.EUR, productFound.getCurrency());

        entityManager.flush();

    }

}
