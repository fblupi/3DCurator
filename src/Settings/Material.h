#ifndef MATERIAL_H
#define MATERIAL_H

#include <vtkSmartPointer.h>
#include <vtkRenderWindow.h>

#include "Core/Sculpture.h"

/**
 * @class Material
 * Class with volume material params
 */
class Material {
public:
    /**
     * Constructor
     * @param ambient   Ambient lighting coefficient
     * @param diffuse   Diffuse lighting coefficient
     * @param specular  Specular lighting coefficient
     * @param power     Specular power
     */
    Material(const double &ambient, const double &diffuse, const double &specular, const double &power);

    /**
     * Destructor
     */
    ~Material();

    /**
     * Set sculpture
     * @param sculpture Sculpture pointer
     */
    void setSculpture(Sculpture* sculpture);

    /**
     * Set volume render window
     * @param volumeRenderWindow    Render window where the volume is being rendered
     */
    void setVolumeRenderWindow(const vtkSmartPointer<vtkRenderWindow> &volumeRenderWindow);

    /**
     * Set ambient coefficient
     * @param ambient   Ambient lighting coefficient
     */
    void setAmbient(const double &ambient);

    /**
     * Set diffuse coefficient
     * @param diffuse   Diffuse lighting coefficient
     */
    void setDiffuse(const double &diffuse);

    /**
     * Set specular coefficient
     * @param specular  Specular lighting coefficient
     */
    void setSpecular(const double &specular);

    /**
     * Set specular power
     * @param power Specular power
     */
    void setPower(const double &power);

    /**
     * Get ambient coefficient
     * @return Ambient lighting coefficient
     */
    double getAmbient() const;

    /**
     * Get diffuse coefficient
     * @return Diffuse lighting coefficient
     */
    double getDiffuse() const;

    /**
     * Get specular coefficient
     * @return Specular lighting coefficient
     */
    double getSpecular() const;

    /**
     * Get specular power
     * @return Specular power
     */
    double getPower() const;

private:
    Sculpture *sculpture; /**< Sculpture pointer */
    vtkSmartPointer<vtkRenderWindow> volumeRenderWindow; /**< Volume render window pointer */
    double ambient; /**< Ambient coefficient */
    double diffuse; /**< Diffuse coefficient */
    double specular; /**< Specular coefficient */
    double power; /**< Specular power */

    /**
     * Update sculpture material
     */
    void update();
};

#endif
