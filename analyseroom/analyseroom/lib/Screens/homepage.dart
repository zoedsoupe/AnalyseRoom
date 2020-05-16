import 'package:flutter/material.dart';
import 'package:Analyseroom/buttons/dropdownRoom.dart';
import 'package:Analyseroom/buttons/raisedButtonForm.dart';
import 'package:Analyseroom/models/text.dart';
import 'package:Analyseroom/models/sizeConfig.dart';

class HomePage extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    SizeConfig().init(context);
    return Scaffold (
      backgroundColor: Colors.grey[900],
      body: Center(
        child: SingleChildScrollView(
                  child: Column(
              //mainAxisAlignment: MainAxisAlignment.center,
              crossAxisAlignment: CrossAxisAlignment.center,
              children: <Widget>[
                SizedBox(height: SizeConfig.screenHeight / 10),
                Image(
                  image: AssetImage('assets/images/IFF.png'),
                  alignment: Alignment.center,
                  width: 95,
                ),
                SizedBox(height: SizeConfig.screenHeight / 4.5,),
                Align(
                  alignment: Alignment(0.04, 0.0),
                  child: DrodownRoom()
                ),
                SizedBox(height: SizeConfig.screenHeight / 20,),
                SizedBox(
                  width: 250,
                  child: FormButton()
                ),
                SizedBox(height: SizeConfig.screenHeight / 5.9,),
                Align(
                  alignment: Alignment.bottomCenter,
                  child: buildText()
                ),
              ],
          ),
        ),
      ),
    );
  }
}
