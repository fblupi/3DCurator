#ifndef BACKGROUNDS_H
#define BACKGROUNDS_H

#include <QColor>

#include <vtkSmartPointer.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>

/**
 * @class Backgrounds
 * Class with widgets background color
 */
class Backgrounds {
public:
    /**
     * Constructor
     * @params meshBackground               Mesh widget background color
     * @params volumeBackground             Volume widget background color
     * @params volumeDeletingBackground     Volume deleting widget background color
     * @params volumeSegmentingBackground   Volume segmenting widget background color
     */
    explicit Backgrounds(QColor meshBackground, QColor volumeBackground, QColor volumeDeletingBackground, QColor volumeSegmentingBackground);

    /**
     * Destructor
     */
    ~Backgrounds();

    /**
     * Set deleting to check if it is being deleting or not
     * @param deleting  Pointer to deleting checker
     */
    void setDeleting(bool *deleting);

    /**
     * Set mesh renderer
     * @param meshRenderer  Mesh renderer
     */
    void setMeshRenderer(const vtkSmartPointer<vtkRenderer> &meshRenderer);

    /**
     * Set volume renderer
     * @param volumeRenderer    Volume renderer
     */
    void setVolumeRenderer(const vtkSmartPointer<vtkRenderer> &volumeRenderer);

    /**
     * Set mesh render window
     * @param meshRenderWindow  Mesh render window
     */
    void setMeshRenderWindow(const vtkSmartPointer<vtkRenderWindow> &meshRenderWindow);

    /**
     * Set volume render window
     * @param volumeRenderWindow  Volume render window
     */
    void setVolumeRenderWindow(const vtkSmartPointer<vtkRenderWindow> &volumeRenderWindow);

    /**
     * Set mesh widget background color
     * @params background   Background color
     */
    void setMeshBackground(const QColor &background);

    /**
     * Set volume widget background color
     * @params background   Background color
     */
    void setVolumeBackground(const QColor &background);

    /**
     * Set volume deleting widget background color
     * @params background   Background color
     */
    void setVolumeDeletingBackground(const QColor &background);

    /**
     * Set volume segmenting background color
     * @params background   Background color
     */
    void setVolumeSegmentingBackground(const QColor &background);

    /**
     * Get mesh widget background color
     * @return Mesh widget background color
     */
    QColor getMeshBackground() const;

    /**
     * Get volume widget background color
     * @return Volume widget background color
     */
    QColor getVolumeBackground() const;

    /**
     * Get volume deleting widget background color
     * @return Volume deleting widget background color
     */
    QColor getVolumeDeletingBackground() const;

    /**
     * Get volume segmenting widget background color
     * @return Volume segmenting widget background color
     */
    QColor getVolumeSegmentingBackground() const;

private:
    QColor meshBackground; /**< Mesh viewer background color */
    QColor volumeBackground; /**< Volume viewer background color */
    QColor volumeDeletingBackground; /**< Volume viewer (delete mode) background color */
    QColor volumeSegmentingBackground; /**< Volume viewer (segmenting) background color */

    bool *deleting; /**< Check if deleting pointer */
    vtkSmartPointer<vtkRenderer> meshRenderer; /**< Mesh renderer pointer */
    vtkSmartPointer<vtkRenderer> volumeRenderer; /**< Volume and slice plane renderer pointer */
    vtkSmartPointer<vtkRenderWindow> meshRenderWindow; /**< Mesh render window pointer */
    vtkSmartPointer<vtkRenderWindow> volumeRenderWindow; /**< Volume and slice plane render window pointer */
};

#endif // BACKGROUNDS_H
