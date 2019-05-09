#ifndef TRANSFERFUNCTION_H
#define TRANSFERFUNCTION_H

#include <vector>
#include <string>
#include <iostream>

#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/foreach.hpp>

#include <vtkSmartPointer.h>
#include <vtkColorTransferFunction.h>
#include <vtkPiecewiseFunction.h>

using boost::property_tree::ptree;

/**
 * Transfer function class. Import-export using XML format
 */
class TransferFunction {
public:
    /**
     * Constructor
     */
    TransferFunction();

    /**
     * Destructor
     */
    ~TransferFunction();

    /**
     * Get color transfer function
     * @return	Color transfer function
     */
    vtkSmartPointer<vtkColorTransferFunction> getColorFun() const;

    /**
     * Get scalar opacity transfer function
     * @return	Scalar opacity transfer function
     */
    vtkSmartPointer<vtkPiecewiseFunction> getScalarFun() const;

    /**
     * Get gradient opacity transfer function
     * @return	Gradient opacity transfer function
     */
    vtkSmartPointer<vtkPiecewiseFunction> getGradientFun() const;

    /**
     * Get transfer function name
     * @return	Transfer function name
     */
    std::string getName() const;

    /**
     * Get transfer function description
     * @return	Transfer function description
     */
    std::string getDescription() const;

    /**
     * Set transfer function name
     * @param	name	Transfer function name
     */
    void setName(const std::string &name);

    /**
     * Set transfer function description
     * @param	description	Transfer function description
     */
    void setDescription(const std::string &description);

    /**
     * Read transfer function from an XML file using its path
     * @param	filename	Path to the input XML file
     */
    void read(std::string &filename);

    /**
     * Read transfer function from an XML file
     * @param	file		Input XML file
     */
    void read(std::istream &file);

    /**
     * Write transfer function in an XML file
     * @param	filename	Path to the output XML file
     */
    void write(std::string &filename);

    /**
     * Clear every point in every part of the transfer function
     */
    void clear();

private:
    std::string name; /**< Transfer function name */
    std::string description; /**< Transfer function description */
    vtkSmartPointer<vtkColorTransferFunction> colorFun; /**< Color transfer function */
    vtkSmartPointer<vtkPiecewiseFunction> scalarFun; /**< Scalar opacity transfer function */
    vtkSmartPointer<vtkPiecewiseFunction> gradientFun; /**< Gradient opacity transfer function */

    /**
     * Read data of transfer function from a tree
     * @param	pt  Tree with transfer function
     */
    void readData(ptree pt);
};

#endif // TRANSFERFUNCTION_H
