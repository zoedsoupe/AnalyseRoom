<?php

require_once './vendor/autoload.php';

use Kreait\Firebase\Factory;

class Database {
    protected  $database;
    protected  $dbname = 'analyseroom';

    public function __construct() {
        $firebase = (new Factory)->withServiceAccount('./secret/analyseroom-fa852944eb11.json');

        $this->database = $firebase->createDatabase();
    }

    public function getData(int $userID = NULL){
        if (empty($userID) || !isset($userID)) { return FALSE; }

        if ($this->database->getReference($this->dbname)->getSnapshot()->hasChild($userID)){
            return $this->database->getReference($this->dbname)->getChild($userID)->getValue();
        } else {
            return FALSE;
        }
    }

    public function insertData(array $data) {
        if (empty($data) || !isset($data)) { return FALSE; }

        foreach ($data as $key => $value){
            $this->database->getReference()->getChild($this->dbname)->getChild($key)->set($value);
        }

        return TRUE;
    }
    
    public function updateData(array $data) {
       if(empty($data) || !isset($data)) return FALSE;
       else {
         $this->database->getReference('db/')->update($data);
         return TRUE;
       }
}

    public function deleteData(int $userID) {
        if (empty($userID) || !isset($userID)) { return FALSE; }

        if ($this->database->getReference($this->dbname)->getSnapshot()->hasChild($userID)){
            $this->database->getReference($this->dbname)->getChild($userID)->remove();
            return TRUE;
        } else {
            return FALSE;
        }
    }
}


