import 'package:flutter/material.dart';
import 'package:firebase_database/firebase_database.dart';

class FireBaseDemoScreen extends StatelessWidget {

  final databaseReference = FirebaseDatabase.instance.reference();
  var controle = 0,
      error = false;
  Map<dynamic, dynamic> room1, room2;

  Widget build (BuildContext context) {
    getData();
    return MaterialApp(
      debugShowCheckedModeBanner: false,
      home: Scaffold(
        appBar: AppBar(
          title: Text('Firebase Connect'),
        ),
        body: Center(
            child: Column(
              crossAxisAlignment: CrossAxisAlignment.stretch,
              children: <Widget>[
                RaisedButton(
                  child: Text('Create Record'),
                  onPressed: () {
                    createRecord();
                  },
                ),
                RaisedButton(
                  child: Text('View Record'),
                  onPressed: () {
                    getData();
                  },
                ),
                RaisedButton(
                  child: Text('Udate Record'),
                  onPressed: () {
                    updateData();
                  },
                ),
                RaisedButton(
                  child: Text('Delete Record'),
                  onPressed: () {
                    deleteData();
                  },
                ),
              ],
            )
        ), //center
      ),
    );
  }

  void createRecord () {
    databaseReference.child("1").set({
      'title': 'Mastering EJB',
      'description': 'Programming Guide for J2EE'
    });
    databaseReference.child("2").set({
      'title': 'Flutter in Action',
      'description': 'Complete Programming Guide to learn Flutter'
    });
  }

  void getData () {
    databaseReference.once().then((DataSnapshot snapshot) {
      print('Data : ${snapshot.value}');
    });
  }

  void updateData () {
    databaseReference.child('1').update({
      'description': 'J2EE complete Reference'
    });
  }

  void deleteData () {
    databaseReference.child('1').remove()
    ;
  }

  void getRoomValues () {

    databaseReference.child('controle').once().then((DataSnapshot snapshot) {
      controle = snapshot.value;
    });

    switch (controle) {
      case 1:
        databaseReference.child('digital1').once().then((
            DataSnapshot room1Val) {
          room1 = room1Val.value;
        });
        break;
      case 2:
        databaseReference.child('digital2').once().then((
            DataSnapshot room2Val) {
          room2 = room2Val.value;
        });
        break;
      default:
        error = true;
    }
  }
//  static Future<List<int>> getControleVal() async {
//    DatabaseReference ref = FirebaseDatabase.instance.reference().child('events');
//    int controle = await ref.once().then((DataSnapshot value) {
//      controle = value.value;
//    });
//  }
}

