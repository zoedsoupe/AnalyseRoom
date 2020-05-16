import 'package:flutter/material.dart';
import 'package:Analyseroom/Screens/loadingScreen.dart';
import 'package:Analyseroom/models/busyRoom.dart';
import 'package:firebase_database/firebase_database.dart';

class RoomPage2 extends StatelessWidget {
  @override


  Widget build(BuildContext context) {
    return StreamBuilder(
      stream: FirebaseDatabase.instance.reference().child('db').child('id').onValue,
      builder: (BuildContext context, AsyncSnapshot<Event> event) {
        if (!event.hasData) {
          return LoadingScreen();
        }
        return BusyRoom(event.data.snapshot.value);
      },
    );
  }
}