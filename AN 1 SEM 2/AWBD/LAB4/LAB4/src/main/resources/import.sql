insert into category(name) values('paintings');

insert into category(name) values('sculptures');

insert into category(name) values('books');



insert into product (id, name, code, reserve_price) values (1, 'The Card Players', 'PCEZ', 250);
insert into info(id, product_id, description) values (1, 1, 'Painting by Cezanne');

insert into product_category (product_id, category_id) values(1,1);
insert into participant(id, first_name, last_name) values (1, 'Will', 'Snow');

insert into product (id, name, code, reserve_price, seller_id) values (2, 'Impression, Sunrise', 'PMON', 300, 1);
insert into info(id, product_id, description) values (2, 2, 'Painting by monet');
insert into product_category (product_id, category_id) values (2, 1);

insert into product (id, name, code, reserve_price, seller_id) values (3, 'Ballon Dog' , 'SJEF', 200, 1);
insert into info (id, product_id, description) values (3, 3 , 'Sculpture by Jeff Koons');
insert into product_category (product_id, category_id) values (3, 2);

