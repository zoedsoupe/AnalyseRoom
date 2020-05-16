import 'package:Analyseroom/Screens/formpage.dart';
import 'package:flutter/material.dart';

class FormButton extends StatefulWidget {
  @override
  _FormButtonState createState() => _FormButtonState();
}

class _FormButtonState extends State<FormButton> {
  @override
  Widget build(BuildContext context) {
    return RaisedButton(
      color: Colors.grey[900],
      child: Text(
        "INFORMAR ERRO",
        style: TextStyle(
          color: Colors.white,
          fontWeight: FontWeight.bold,
          fontSize: 15,
        ),
      ),
      onPressed: () {
        Navigator.push(
          context, 
          MaterialPageRoute(
            builder: (context) => FormPage()
          )
        );
      },
    );
  }
}
