#include "regionGrowingDeleter.h"

Coord2D searchInitialVoxel(vtkSmartPointer<vtkImageData> imageData, const int ijk[3], const Bounds bounds) {
	if (ijk[0] - 1 >= bounds.MIN_X
		&& imageData->GetScalarComponentAsDouble(ijk[0] - 1, ijk[1], ijk[2], 0) >= MIN_AIR) {
		return{ ijk[0] - 1, ijk[1] };
	}
	else if (ijk[0] + 1 < bounds.MAX_X
		&& imageData->GetScalarComponentAsDouble(ijk[0] + 1, ijk[1], ijk[2], 0) >= MIN_AIR) {
		return{ ijk[0] + 1, ijk[1] };
	}
	else if (ijk[1] - 1 >= bounds.MIN_Y
		&& imageData->GetScalarComponentAsDouble(ijk[0], ijk[1] - 1, ijk[2], 0) >= MIN_AIR) {
		return{ ijk[0], ijk[1] - 1 };
	}
	else if (ijk[1] + 1 < bounds.MAX_Y
		&& imageData->GetScalarComponentAsDouble(ijk[0], ijk[1] + 1, ijk[2], 0) >= MIN_AIR) {
		return{ ijk[0], ijk[1] + 1 };
	}
	else if (ijk[0] - 1 >= bounds.MIN_X && ijk[1] - 1 >= bounds.MIN_Y
		&& imageData->GetScalarComponentAsDouble(ijk[0] - 1, ijk[1] - 1, ijk[2], 0) >= MIN_AIR) {
		return{ ijk[0] - 1, ijk[1] - 1 };
	}
	else if (ijk[0] - 1 >= bounds.MIN_X && ijk[1] + 1 < bounds.MAX_Y
		&& imageData->GetScalarComponentAsDouble(ijk[0] - 1, ijk[1] + 1, ijk[2], 0) >= MIN_AIR) {
		return{ ijk[0] - 1, ijk[1] + 1 };
	}
	else if (ijk[0] + 1 < bounds.MAX_X && ijk[1] - 1 >= bounds.MIN_Y
		&& imageData->GetScalarComponentAsDouble(ijk[0] + 1, ijk[1] - 1, ijk[2], 0) >= MIN_AIR) {
		return{ ijk[0] + 1, ijk[1] - 1 };
	}
	else if (ijk[0] + 1 < bounds.MAX_X && ijk[1] + 1 < bounds.MAX_Y
		&& imageData->GetScalarComponentAsDouble(ijk[0] + 1, ijk[1] + 1, ijk[2], 0) >= MIN_AIR) {
		return{ ijk[0] + 1, ijk[1] + 1 };
	}
	else {
		return{ ijk[0], ijk[1] };
	}
}

void deleteImage(vtkSmartPointer<vtkImageData> imageData, const int ijk[3], const Bounds bounds) {
	Coord2D ij;
	std::queue<Coord2D> queue;

	ij[0] = ijk[0]; 
	ij[1] = ijk[1];

	if (imageData->GetScalarComponentAsDouble(ijk[0], ijk[1], ijk[2], 0) < MIN_AIR) {
		ij = searchInitialVoxel(imageData, ijk, bounds);
	}

	queue.push(ij);
	while (!queue.empty()) {
		ij = queue.front();
		queue.pop();
		if (ij[0] < bounds.MAX_X && ij[0] >= bounds.MIN_X && ij[1] < bounds.MAX_Y && ij[1] >= bounds.MIN_Y) {
			if (imageData->GetScalarComponentAsDouble(ij[0], ij[1], ijk[2], 0) >= MIN_AIR) {
				imageData->SetScalarComponentFromDouble(ij[0], ij[1], ijk[2], 0, AIR_HU);
				queue.push({ ij[0] - 1, ij[1] - 1 });
				queue.push({ ij[0] - 1, ij[1] });
				queue.push({ ij[0] - 1, ij[1] + 1 });
				queue.push({ ij[0], ij[1] - 1 });
				queue.push({ ij[0], ij[1] + 1 });
				queue.push({ ij[0] + 1, ij[1] - 1 });
				queue.push({ ij[0] + 1, ij[1] });
				queue.push({ ij[0] + 1, ij[1] + 1 });
			}
		}
	}
}

void deleteByImages(vtkSmartPointer<vtkImageData> imageData, const int ijk[3], const Bounds bounds) {
	int xyz[3] = { ijk[0], ijk[1], ijk[2] };

	deleteImage(imageData, xyz, bounds);

	xyz[2] = ijk[2] + 1;
	while (xyz[2] < bounds.MAX_Z) {
		deleteImage(imageData, xyz, bounds);
		xyz[2] = xyz[2] + 1;
	}

	xyz[2] = ijk[2] - 1;
	while (xyz[2] >= bounds.MIN_Z) {
		deleteImage(imageData, xyz, bounds);
		xyz[2] = xyz[2] - 1;
	}
}