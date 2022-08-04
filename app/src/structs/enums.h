#ifndef ENUMS_H
#define ENUMS_H

/************************
 *
 * Align & Distribute
 *
 * **********************/

enum class AlignmentReference {
    FirstSelected = 0,
    LastSelected = 1,
    Selection = 2,
    Page = 3,
    Margins = 4,
    Guides = 5
};

enum class AlignmentMode {
    Move = 0,
    Size = 1
};

/************************
 *
 * Color
 *
 * **********************/

/** Scribus color models */
enum class ColorModel{
    RGB = 0,
    CMYK = 1,
    Lab = 2,
    HSV = 3
};

enum class ItemFillMode {
    Solid = 0,
    Gradient = 1,
    Pattern = 2,
    Image = 3
};

enum class GradientType {
    Linear = 0,
    Radial = 1,
    Conical = 2,
    Diamond = 3,
    FourColors = 4,
    Mesh = 5,
    PatchMesh = 6
};

enum class ColorBlendMode {

    Normal = 0,
    Darken = 1,
    Lighten = 2,
    Multiply = 3,
    Screen = 4,
    Overlay = 5,
    HardLight = 6,
    SoftLight = 7,
    Difference = 8,
    Exclusion = 9,
    ColorDodge = 10,
    ColorBurn = 11,
    Hue = 12,
    Saturation = 13,
    Color = 14,
    Luminosity = 15
};

enum class ColorPickerConfig {
    Default = 0,
    Fill = 1,
    FillMask = 2,
    Stroke = 3,
    StrokeMask = 4,
    Shadow = 5,
    Text = 6
};


/************************
 *
 * Line
 *
 * **********************/

enum class ArrowDirection
{
    StartArrow = 0,
    EndArrow = 1
};

/************************
 *
 * Page
 *
 * **********************/

enum class PageLayout {
    Single = 0,
    Double = 1,
    ThreeFacing = 2,
    FourFacing = 3
};

enum class FirstPage {
    Left = 0,
    MiddleLeft = 1,
    Middle = 2,
    MiddleRight = 3,
    Right

};

enum class PageInsert {
    After = 0,
    Before = 1,
    AtEnd = 2,
    Swap = 3
};

/************************
 *
 * Text
 *
 * **********************/

enum class TextOnPathType {
    Default = 0,
    StairStep = 1,
    Skew = 2

};

enum class ListType {
    None = 0,
    DropCap = 1,
    Bullet = 2,
    Numbered = 3


};

#endif // ENUMS_H
