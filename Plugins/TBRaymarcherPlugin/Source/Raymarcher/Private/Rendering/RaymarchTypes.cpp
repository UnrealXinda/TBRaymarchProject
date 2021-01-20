// Created by Tommy Bazar. No rights reserved :)
// Special credits go to : Temaran (compute shader tutorial), TheHugeManatee (original concept, supervision)
// and Ryan Brucks (original raymarching code).

#include "Rendering/RaymarchTypes.h"

FString GetDirectionName(FCubeFace Face)
{
	switch (Face)
	{
		case FCubeFace::XPositive:
			return FString("+X");
		case FCubeFace::XNegative:
			return FString("-X");
		case FCubeFace::YPositive:
			return FString("+Y");
		case FCubeFace::YNegative:
			return FString("-Y");
		case FCubeFace::ZPositive:
			return FString("+Z");
		case FCubeFace::ZNegative:
			return FString("-Z");
		default:
			return FString("Something went wrong here!");
	}
}

FMajorAxes FMajorAxes::GetMajorAxes(FVector LightPos)
{
	FMajorAxes RetVal;
	TArray<TTuple<FCubeFace, float>> FaceVector;

	for (int i = 0; i < 6; i++)
	{
		// Dot of position and face normal yields cos(angle)
		float Weight = FVector::DotProduct(FCubeFaceNormals[i], LightPos);

		// Need to make sure we go along the axis with a positive weight, not negative.
		Weight = (Weight > 0 ? Weight * Weight : 0);
		RetVal.FaceWeights.Add(MakeTuple(FCubeFace(i), Weight));
	}
	// Sort so that the 3 major axes are the first.
	RetVal.FaceWeights.Sort([](const auto& A, const auto& B) { return A.Value > B.Value; });

	return RetVal;
}
