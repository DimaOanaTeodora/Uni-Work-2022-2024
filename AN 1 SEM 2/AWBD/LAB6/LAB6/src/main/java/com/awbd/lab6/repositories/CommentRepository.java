package com.awbd.lab6.repositories;

import com.awbd.lab6.domain.Comment;
import org.springframework.data.mongodb.repository.MongoRepository;

public interface CommentRepository extends MongoRepository<Comment, String> {

}
