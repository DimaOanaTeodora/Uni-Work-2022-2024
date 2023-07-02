package com.awbd.lab4.repositories;


import com.awbd.lab4.domain.Participant;
import lombok.extern.slf4j.Slf4j;
import org.junit.jupiter.api.MethodOrderer;
import org.junit.jupiter.api.Order;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.TestMethodOrder;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.autoconfigure.jdbc.AutoConfigureTestDatabase;
import org.springframework.boot.test.autoconfigure.orm.jpa.DataJpaTest;
import org.springframework.test.annotation.Rollback;
import org.springframework.test.context.ActiveProfiles;

import java.util.Arrays;
import java.util.List;

import static org.junit.jupiter.api.Assertions.assertFalse;

@DataJpaTest
@ActiveProfiles("mysql")
@AutoConfigureTestDatabase(replace = AutoConfigureTestDatabase.Replace.NONE)
@TestMethodOrder(MethodOrderer.OrderAnnotation.class)
@Rollback(false)
@Slf4j
public class ParticipantRepositoryTest {

    @Autowired
    private ParticipantRepository participantRepository;

    @Test
    @Order(1)
    public void addParticipant() {
        Participant participant = new Participant();
        participant.setFirstName("John");
        participant.setLastName("Adam");
        participantRepository.save(participant);
    }

    @Test
    @Order(2)
    public void findByName() {
        List<Participant> participants = participantRepository.findByLastNameLike("%da%");
        assertFalse(participants.isEmpty());
        log.info("findByLastNameLike ...");
        participants.forEach(participant -> log.info(participant.getLastName()));
    }

    @Test
    @Order(3)
    public void findByIds() {
        List<Participant> participants = participantRepository.findByIdIn(Arrays.asList(1L,2L));
        assertFalse(participants.isEmpty());
        log.info("findByIds ...");
        participants.forEach(participant -> log.info(participant.getLastName()));
    }

}
