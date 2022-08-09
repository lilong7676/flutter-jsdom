import 'package:flutter/material.dart';

class ShapePainter extends CustomPainter {
  late final Animation<double> factor;

  ShapePainter({required this.factor}) : super(repaint: factor);

  @override
  void paint(Canvas canvas, Size size) {
    Paint paint = Paint()
      ..color = Color.lerp(Colors.red, Colors.blue, factor.value)!;
    canvas.drawCircle(
        Offset(size.width / 2, size.height / 2), size.width / 2, paint);
  }

  @override
  bool shouldRepaint(covariant ShapePainter oldDelegate) {
    return oldDelegate.factor != factor;
  }
}
