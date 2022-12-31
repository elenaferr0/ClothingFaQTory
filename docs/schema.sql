CREATE TABLE IF NOT EXISTS product
(
    id
    SERIAL
    PRIMARY
    KEY,
    code
    varchar
(
    20
) NOT NULL UNIQUE,
    color varchar
(
    50
) NOT NULL,
    sold_quantity int DEFAULT 0,
    available_quantity int DEFAULT 0,
    description TEXT DEFAULT NULL,
    size_id int NOT NULL,
    material_id int NOT null
    );

CREATE TABLE IF NOT EXISTS size
(
    id
    SERIAL
    PRIMARY
    KEY,
    name
    varchar
(
    10
) UNIQUE NOT NULL,
    extra_percentage_of_material INT
    );

ALTER TABLE product
    ADD CONSTRAINT fk_product_size_id FOREIGN KEY (size_id) REFERENCES size (id);

CREATE TABLE IF NOT EXISTS material
(
    id
    SERIAL
    PRIMARY
    KEY,
    name
    varchar
(
    50
) UNIQUE NOT NULL,
    cost_per_unit REAL DEFAULT 0,
    unit_of_measure varchar
(
    20
)
    );

ALTER TABLE product
    ADD CONSTRAINT fk_product_material_id FOREIGN KEY (material_id) REFERENCES material (id);

-- CLOTHING ITEM CHILDREN TABLES
CREATE TABLE IF NOT EXISTS clothing_item
(
    sustainable_materials
    BOOL
    DEFAULT
    FALSE,
    gender
    varchar
(
    20
) DEFAULT 'UNISEX'
    ) INHERITS
(
    product
);

CREATE TABLE IF NOT EXISTS vest
(
    has_buttons BOOL DEFAULT FALSE
) INHERITS
(
    clothing_item
);

CREATE TABLE IF NOT EXISTS jeans
(
    shorts BOOL DEFAULT FALSE
) INHERITS
(
    clothing_item
);

CREATE TABLE IF NOT EXISTS overalls
(
) INHERITS
(
    vest,
    jeans
);

-- ACCESSORY CHILDREN TABLES
CREATE TABLE IF NOT EXISTS accessory
(
    category varchar
(
    30
) NOT NULL
    ) INHERITS
(
    product
);

CREATE TABLE IF NOT EXISTS backpack
(
    capacity REAL NOT NULL
) INHERITS
(
    accessory
);

CREATE TABLE IF NOT EXISTS hat
(
    is_baseball_cap bool DEFAULT true
) INHERITS
(
    accessory
);

CREATE TABLE IF NOT EXISTS bracelet
(
    pearl_number
    int
    NOT
    NULL,
    pearl_diameter
    REAL
    NOT
    null
) INHERITS
(
    accessory
);
