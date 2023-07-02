package com.awbd.lab4.services;

import com.awbd.lab4.domain.Product;
import org.springframework.web.multipart.MultipartFile;

public interface PhotoService {
    void savePhotoFile(Product product, MultipartFile file);
}
