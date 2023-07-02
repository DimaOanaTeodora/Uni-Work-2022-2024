package com.awbd.lab6.services;

import com.awbd.lab6.domain.Movie;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.Pageable;

import java.util.List;
import java.util.Optional;

public interface MovieService {
    public List<Movie> findAll();
    public Optional<Movie> findById(String id);
    public void deleteById(String id);
    Page<Movie> findPaginated(Pageable pageable);
}
