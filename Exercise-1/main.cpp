#include <iostream>
#include <fstream>
#include <array>

#include "Eigen.h"
#include "VirtualSensor.h"

struct Vertex
{
	EIGEN_MAKE_ALIGNED_OPERATOR_NEW

	// position stored as 4 floats (4th component is supposed to be 1.0)
	Vector4f position;
	// color stored as 4 unsigned char
	Vector4uc color;
};

float calculate_edge_length(Vertex* vertices, int idx1, int idx2) {
	return (vertices[idx1].position.head<3>() - vertices[idx2].position.head<3>()).norm();
}


bool WriteMesh(Vertex* vertices, unsigned int width, unsigned int height, const std::string& filename)
{
	float edgeThreshold = 0.01f; // 1cm

	// TODO 2: use the OFF file format to save the vertices grid (http://www.geomview.org/docs/html/OFF.html)
	// - have a look at the "off_sample.off" file to see how to store the vertices and triangles
	// - for debugging we recommend to first only write out the vertices (set the number of faces to zero)
	// - for simplicity write every vertex to file, even if it is not valid (position.x() == MINF) (note that all vertices in the off file have to be valid, thus, if a point is not valid write out a dummy point like (0,0,0))
	// - use a simple triangulation exploiting the grid structure (neighboring vertices build a triangle, two triangles per grid cell)
	// - you can use an arbitrary triangulation of the cells, but make sure that the triangles are consistently oriented
	// - only write triangles with valid vertices and an edge length smaller then edgeThreshold	

	// TODO: Get number of vertices
	unsigned int nVertices = 0;
	nVertices = width * height;

	// TODO: Determine number of valid faces
	unsigned nFaces = 0;
    // nFaces = (width - 1) * (height - 1) * 2;

	for (size_t row = 0; row < height - 1; row++) {
        for (size_t col = 0; col < width - 1; col++) {
            size_t idx0 = row * width + col;
            size_t idx1 = row * width + (col + 1);
            size_t idx2 = (row + 1) * width + col;
            size_t idx3 = (row + 1) * width + (col + 1);

            if (vertices[idx0].position.z() != MINF && 
                vertices[idx1].position.z() != MINF && 
                vertices[idx2].position.z() != MINF) {
                float d01 = calculate_edge_length(vertices, idx0, idx1); 
                float d02 = calculate_edge_length(vertices, idx0, idx2);
                float d12 = calculate_edge_length(vertices, idx1, idx2);
                if (d01 < edgeThreshold && d02 < edgeThreshold && d12 < edgeThreshold) {
                    nFaces++;
                }
            }

            if (vertices[idx1].position.z() != MINF && 
                vertices[idx2].position.z() != MINF && 
                vertices[idx3].position.z() != MINF) {
               	float d12 = calculate_edge_length(vertices, idx1, idx2);
               	float d23 = calculate_edge_length(vertices, idx2, idx3);
               	float d31 = calculate_edge_length(vertices, idx3, idx1);
                if (d12 < edgeThreshold && d23 < edgeThreshold && d31 < edgeThreshold) {
                    nFaces++;
                }
            }
        }
    }


	// Write off file
	std::ofstream outFile(filename);
	if (!outFile.is_open()) return false;

	// write header
	outFile << "COFF" << std::endl;

	outFile << "# numVertices numFaces numEdges" << std::endl;
	outFile << nVertices << " " << nFaces << " 0" << std::endl;


	// TODO: save vertices
    outFile << "# list of vertices" << std::endl;
    outFile << "# X Y Z R G B A" << std::endl;

	for (size_t row = 0; row < height; row++) {
		for (size_t col = 0; col < width; col++) {
			size_t idx = row * width + col;

			if (vertices[idx].position.z() == MINF) {
				outFile << "0 0 0 0 0 0 0" << std::endl;
			} else {
				outFile << vertices[idx].position.x() << " " 
						<< vertices[idx].position.y() << " " 
						<< vertices[idx].position.z() << " "
						<< static_cast<int>(vertices[idx].color.x()) << " " 
						<< static_cast<int>(vertices[idx].color.y()) << " " 
						<< static_cast<int>(vertices[idx].color.z()) << " " 
						<< static_cast<int>(vertices[idx].color.w()) << std::endl;
			}
		}
	}

	// for (size_t idx = 0; idx < width * height; idx++) {   
    //     if (vertices[idx].position.z() == MINF) {
    //         outFile << "0 0 0 0 0 0 0" << std::endl;
    //     } else {
    //         outFile << vertices[idx].position.x() << " " 
    //                 << vertices[idx].position.y() << " " 
    //                 << vertices[idx].position.z() << " "
    //                 << static_cast<int>(vertices[idx].color.x()) << " " 
    //                 << static_cast<int>(vertices[idx].color.y()) << " " 
    //                 << static_cast<int>(vertices[idx].color.z()) << " " 
    //                 << static_cast<int>(vertices[idx].color.w()) << std::endl;
    //     }
    // }
    

	// TODO: save valid faces
	outFile << "# list of faces" << std::endl;
	outFile << "# nVerticesPerFace idx0 idx1 idx2 ..." << std::endl;

	for (size_t row = 0; row < height - 1; row++) {
		for (size_t col = 0; col < width - 1; col++) {
			size_t idx0 = row * width + col;
			size_t idx1 = row * width + (col + 1);
			size_t idx2 = (row + 1) * width + col;
			size_t idx3 = (row + 1) * width + (col + 1);

 
			if (vertices[idx0].position.z() != MINF && 
                vertices[idx1].position.z() != MINF && 
                vertices[idx2].position.z() != MINF) {
                float d01 = calculate_edge_length(vertices, idx0, idx1); 
                float d02 = calculate_edge_length(vertices, idx0, idx2);
                float d12 = calculate_edge_length(vertices, idx1, idx2);
                if (d01 < edgeThreshold && d02 < edgeThreshold && d12 < edgeThreshold) {
                    outFile << "3 " << idx0 << " " << idx2 << " " << idx1 << std::endl;
                }
            }

            if (vertices[idx1].position.z() != MINF && 
                vertices[idx2].position.z() != MINF && 
                vertices[idx3].position.z() != MINF) {
                float d12 = calculate_edge_length(vertices, idx1, idx2);
                float d23 = calculate_edge_length(vertices, idx2, idx3);
                float d31 = calculate_edge_length(vertices, idx3, idx1);
                if (d12 < edgeThreshold && d23 < edgeThreshold && d31 < edgeThreshold) {
                    outFile << "3 " << idx2 << " " << idx3 << " " << idx1 << std::endl;
                }
            }
		}
	}
	
	

	// close file
	outFile.close();

	return true;
}

int main()
{
	// Make sure this path points to the data folder
	std::string filenameIn = "../../Data/rgbd_dataset_freiburg1_xyz/";
	std::string filenameBaseOut = "mesh_";

	// load video
	std::cout << "Initialize virtual sensor..." << std::endl;
	VirtualSensor sensor;
	if (!sensor.Init(filenameIn))
	{
		std::cout << "Failed to initialize the sensor!\nCheck file path!" << std::endl;
		return -1;
	}

	// convert video to meshes
	while (sensor.ProcessNextFrame())
	{
		// get ptr to the current depth frame
		// depth is stored in row major (get dimensions via sensor.GetDepthImageWidth() / GetDepthImageHeight())
		float* depthMap = sensor.GetDepth();
		// get ptr to the current color frame
		// color is stored as RGBX in row major (4 byte values per pixel, get dimensions via sensor.GetColorImageWidth() / GetColorImageHeight())
		BYTE* colorMap = sensor.GetColorRGBX();

		// get depth intrinsics
		Matrix3f depthIntrinsics = sensor.GetDepthIntrinsics();
		Matrix3f depthIntrinsicsInv = depthIntrinsics.inverse();  //K⁻1

		float fX = depthIntrinsics(0, 0);
		float fY = depthIntrinsics(1, 1);
		float cX = depthIntrinsics(0, 2);
		float cY = depthIntrinsics(1, 2);

		// compute inverse depth extrinsics
		Matrix4f depthExtrinsicsInv = sensor.GetDepthExtrinsics().inverse();  //E⁻1

		Matrix4f trajectory = sensor.GetTrajectory();
		Matrix4f trajectoryInv = sensor.GetTrajectory().inverse();

		// TODO 1: back-projection
		// write result to the vertices array below, keep pixel ordering!
		// if the depth value at idx is invalid (MINF) write the following values to the vertices array
		// vertices[idx].position = Vector4f(MINF, MINF, MINF, MINF);
		// vertices[idx].color = Vector4uc(0,0,0,0);
		// otherwise apply back-projection and transform the vertex to world space, use the corresponding color from the colormap
		Vertex* vertices = new Vertex[sensor.GetDepthImageWidth() * sensor.GetDepthImageHeight()];

		for (size_t row = 0; row < sensor.GetDepthImageHeight(); row++) {
            for (size_t col = 0; col < sensor.GetDepthImageWidth(); col++) {
                size_t idx = row * sensor.GetDepthImageWidth() + col;
				size_t color_idx = row * sensor.GetColorImageWidth() + col;
                float depth = depthMap[idx];
				Vector4f world_point;
                Vector4uc color_values;
		
				if (!(depth == MINF)) {
					Vector3f pixel = Vector3f(col, row, 1.0f) * depth;  
					Vector3f camera_point = depthIntrinsicsInv * pixel;
					Vector4f camera_point_homogeneous(camera_point.x(), camera_point.y(), camera_point.z(), 1.0f);
					world_point = trajectoryInv * depthExtrinsicsInv * camera_point_homogeneous;
					color_values = Vector4uc(
						colorMap[color_idx * 4 + 0], 
						colorMap[color_idx * 4 + 1], 
						colorMap[color_idx * 4 + 2], 
						colorMap[color_idx * 4 + 3]
					);
					vertices[idx].position = world_point;
            		vertices[idx].color = color_values;
				}
				else {
					vertices[idx].position = Vector4f(MINF, MINF, MINF, MINF);
            		vertices[idx].color = Vector4uc(0, 0, 0, 0);
				}		
           }
        }


		// write mesh file
		std::stringstream ss;
		ss << filenameBaseOut << sensor.GetCurrentFrameCnt() << ".off";
		if (!WriteMesh(vertices, sensor.GetDepthImageWidth(), sensor.GetDepthImageHeight(), ss.str()))
		{
			std::cout << "Failed to write mesh!\nCheck file path!" << std::endl;
			return -1;
		}

        

		// free mem
		delete[] vertices;
	}

	return 0;
}