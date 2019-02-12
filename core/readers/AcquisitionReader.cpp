
#include "io/primitives.h"
#include "mri_core_data.h"

#include "AcquisitionReader.h"

namespace Gadgetron::Core::Readers {


    Core::Message AcquisitionReader::read(std::istream &stream) {

        using namespace Core;
        using namespace std::literals;


        auto header = IO::read<ISMRMRD::AcquisitionHeader>(stream);


        optional<hoNDArray<float>> trajectory = boost::none;
        if (header.trajectory_dimensions) {
            trajectory = hoNDArray<float>(header.trajectory_dimensions,
                                          header.number_of_samples);

            IO::read(stream, trajectory->data(),trajectory->size());
        }

        auto data = hoNDArray<std::complex<float>>(header.number_of_samples,
                                                   header.active_channels);
        IO::read(stream, data.data(),data.size());

        return Core::Message(header, trajectory, data);
    }

    uint16_t AcquisitionReader::slot() {
        return 1008;
    }

    GADGETRON_READER_EXPORT(AcquisitionReader)
}


