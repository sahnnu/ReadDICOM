#include <iostream>
#include <dcmtk/dcmdata/dcfilefo.h>  // For DcmFileFormat
#include <dcmtk/dcmdata/dcitem.h>    // For DcmDataset
#include <dcmtk/dcmdata/dcdeftag.h>   // For DICOM tag definitions
#include <dcmtk/dcmdata/dcerror.h>    // For OFCondition
#include <dcmtk/dcmimgle/dcmimage.h>   // For DicomImage
#include <dcmtk/dcmjpeg/djdecode.h>    // JPEG support
#include <dcmtk/dcmjpeg/djencode.h>
#include <dcmtk/dcmjpeg/djrploss.h>    // For JPEG encoder
#include <dcmtk/dcmimage/diregist.h>   // Image format registration (required for DicomImage)
#include <dcmtk/dcmdata/dcrledrg.h>    // For RLE decompression

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <DICOM file>" << std::endl;
        return 1;
    }

    const char* filename = "D:\Assignment\ReadDICOM327.dcm";

    // Load the DICOM file
    DcmFileFormat fileformat;
    OFCondition status = fileformat.loadFile(filename);

    if (!status.good())
    {
        std::cerr << "Error: " << status.text() << std::endl;
        return 1;
    }

    // Get the dataset from the file
    DcmDataset* dataset = fileformat.getDataset();

    // Print patient information
    OFString patientName;
    OFString patientID;
    OFString patientBirthDate;
    OFString patientSex;

    if (dataset->findAndGetOFString(DCM_PatientName, patientName).good())
    {
        std::cout << "Patient Name: " << patientName << std::endl;
    }
    else
    {
        std::cout << "Patient Name: Not available" << std::endl;
    }

    if (dataset->findAndGetOFString(DCM_PatientID, patientID).good())
    {
        std::cout << "Patient ID: " << patientID << std::endl;
    }
    else
    {
        std::cout << "Patient ID: Not available" << std::endl;
    }

    if (dataset->findAndGetOFString(DCM_PatientBirthDate, patientBirthDate).good())
    {
        std::cout << "Patient Birth Date: " << patientBirthDate << std::endl;
    }
    else
    {
        std::cout << "Patient Birth Date: Not available" << std::endl;
    }

    if (dataset->findAndGetOFString(DCM_PatientSex, patientSex).good())
    {
        std::cout << "Patient Sex: " << patientSex << std::endl;
    }
    else
    {
        std::cout << "Patient Sex: Not available" << std::endl;
    }

    // Print study information
    OFString studyDate;
    OFString studyTime;
    OFString studyDescription;

    if (dataset->findAndGetOFString(DCM_StudyDate, studyDate).good())
    {
        std::cout << "Study Date: " << studyDate << std::endl;
    }
    else
    {
        std::cout << "Study Date: Not available" << std::endl;
    }

    if (dataset->findAndGetOFString(DCM_StudyTime, studyTime).good())
    {
        std::cout << "Study Time: " << studyTime << std::endl;
    }
    else
    {
        std::cout << "Study Time: Not available" << std::endl;
    }

    if (dataset->findAndGetOFString(DCM_StudyDescription, studyDescription).good())
    {
        std::cout << "Study Description: " << studyDescription << std::endl;
    }
    else
    {
        std::cout << "Study Description: Not available" << std::endl;
    }

    // Print series information
    OFString seriesNumber;
    OFString modality;
    OFString seriesDescription;

    if (dataset->findAndGetOFString(DCM_SeriesNumber, seriesNumber).good())
    {
        std::cout << "Series Number: " << seriesNumber << std::endl;
    }
    else
    {
        std::cout << "Series Number: Not available" << std::endl;
    }

    if (dataset->findAndGetOFString(DCM_Modality, modality).good())
    {
        std::cout << "Modality: " << modality << std::endl;
    }
    else
    {
        std::cout << "Modality: Not available" << std::endl;
    }

    if (dataset->findAndGetOFString(DCM_SeriesDescription, seriesDescription).good())
    {
        std::cout << "Series Description: " << seriesDescription << std::endl;
    }
    else
    {
        std::cout << "Series Description: Not available" << std::endl;
    }
    // Extract and print Image Height (Rows) and Width (Columns)
    Uint16 rows, columns;
    if (dataset->findAndGetUint16(DCM_Rows, rows).good() && 
        dataset->findAndGetUint16(DCM_Columns, columns).good()) {
        std::cout << "Image Height (Rows): " << rows << std::endl;
        std::cout << "Image Width (Columns): " << columns << std::endl;
    } else {
        std::cerr << "Error: Could not find Image Height/Width" << std::endl;
    }


     DicomImage dicomImage(dicomFile);
    if (dicomImage.getStatus() == EIS_Normal) {
        if (dicomImage.getWindowCount() > 0) {
            dicomImage.setWindow(0); // Set to the first window if multiple windows are present
        }

        const char* outputFile = "D:\\Assignment\\Dicom2JPEG.jpeg";
        if (dicomImage.writeJPEG(outputFile, 100, 90)) {
            std::cout << "JPEG image saved to: " << outputFile << std::endl;
        } else {
            std::cerr << "Error: Failed to write JPEG image" << std::endl;
        }
    } else {
        std::cerr << "Error: DICOM image is not normal (" 
                  << DicomImage::getString(dicomImage.getStatus()) << ")" << std::endl;
    }

    // Clean up JPEG decompression
    DJDecoderRegistration::cleanup();

    return 0;
}
