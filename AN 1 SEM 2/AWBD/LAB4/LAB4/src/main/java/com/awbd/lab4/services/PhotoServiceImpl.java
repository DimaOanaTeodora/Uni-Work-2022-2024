package com.awbd.lab4.services;

import com.awbd.lab4.domain.Info;
import com.awbd.lab4.domain.Product;
import com.awbd.lab4.repositories.ProductRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;
import org.springframework.web.multipart.MultipartFile;

import java.io.IOException;

@Service
public class PhotoServiceImpl implements PhotoService {
    ProductRepository productRepository;

    @Autowired
    public PhotoServiceImpl(ProductRepository productRepository) {
        this.productRepository = productRepository;
    }

    @Override
    public void savePhotoFile(Product product, MultipartFile file) {
        try {


            Byte[] byteObjects = new Byte[file.getBytes().length];
            int i = 0; for (byte b : file.getBytes()){
                byteObjects[i++] = b; }

            Info info = product.getInfo();
            if (info == null) {
                info = new Info();
            }

            info.setProduct(product);
            product.setInfo(info);

            if (byteObjects.length > 0){
                info.setPhoto(byteObjects);
            }

            productRepository.save(product);
        }
        catch (IOException e) {
        }

    }
}
