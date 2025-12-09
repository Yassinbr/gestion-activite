-- Script de création de la table ACTIVITES
-- Assurez-vous d'être connecté à la base de données Oracle avant d'exécuter ce script

-- Créer la table ACTIVITES
CREATE TABLE ACTIVITES (
    ID_ACTIVITE NUMBER PRIMARY KEY,
    NOM VARCHAR2(100) NOT NULL,
    TELEPHONE VARCHAR2(20) NOT NULL,
    TYPE VARCHAR2(50),
    DUREE NUMBER,
    CAPACITE NUMBER,
    DATE_CREATION TIMESTAMP DEFAULT SYSDATE
);

-- Créer une séquence pour l'ID_ACTIVITE
CREATE SEQUENCE seq_activites
    START WITH 1
    INCREMENT BY 1
    NOCACHE;

-- Créer un trigger pour auto-incrémenter l'ID
CREATE OR REPLACE TRIGGER trg_activites_id
BEFORE INSERT ON ACTIVITES
FOR EACH ROW
BEGIN
    IF :NEW.ID_ACTIVITE IS NULL THEN
        SELECT seq_activites.NEXTVAL INTO :NEW.ID_ACTIVITE FROM DUAL;
    END IF;
END;
/

-- Insérer quelques données de test
INSERT INTO ACTIVITES (NOM, TELEPHONE, TYPE, DUREE, CAPACITE) 
VALUES ('Yoga', '21650123456', 'Sport', 60, 15);

INSERT INTO ACTIVITES (NOM, TELEPHONE, TYPE, DUREE, CAPACITE) 
VALUES ('Danse', '21650654321', 'Loisir', 45, 20);

INSERT INTO ACTIVITES (NOM, TELEPHONE, TYPE, DUREE, CAPACITE) 
VALUES ('Natation', '21699123456', 'Sport', 90, 25);

COMMIT;

-- Vérifier les données insérées
SELECT * FROM ACTIVITES;
