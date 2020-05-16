import 'package:Analyseroom/Screens/roompage.dart';
import 'package:flutter/material.dart';

class DrodownRoom extends StatefulWidget {
  @override
  _DrodownRoomState createState() => _DrodownRoomState();
}

class _DrodownRoomState extends State<DrodownRoom> {

  String dropdownValue = ''; 

  @override
  Widget build(BuildContext context) {
    return DropdownButtonHideUnderline(
      child: DropdownButton(
          icon: Icon(Icons.arrow_downward),
          iconSize: 24,
          elevation: 16,
          isDense: false,
          isExpanded: false,
          hint: Text(
              "SALAS",
              style: TextStyle(
                  color: Colors.white,
                  fontWeight: FontWeight.bold,
                  fontSize: 16,
              ),
          ),
          onChanged: (String newValue) {
            setState(() {
              dropdownValue = newValue;
              Navigator.push(
                  context,
                  MaterialPageRoute(
                      builder: (context) => RoomPageBuilderFireBase()
                  )
              );
            });
          },
          items: <String>['SALAE1']
              .map<DropdownMenuItem<String>>((String value) {
            return DropdownMenuItem<String>(
              value: value,
              child: Center(
                child: Text(
                    value,
                    style: TextStyle(
                      fontSize: 14,
                      color: Colors.white,
                      fontWeight: FontWeight.bold
                    )
                  ),
              ),
            );
          }).toList(),
      ),
    );
  }
}
