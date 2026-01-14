// Fill out your copyright notice in the Description page of Project Settings.


#include "Mover.h"

// Sets default values for this component's properties
UMover::UMover()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMover::BeginPlay()
{
	Super::BeginPlay();

	float MyFloat = 10.0f;
	float* FloatPtr = &MyFloat;

	float Result = *FloatPtr + 5.0f; // 15.0f
	UE_LOG(LogTemp, Display, TEXT("Result: %f"), Result);

	*FloatPtr = 30.0f;
	UE_LOG(LogTemp, Display, TEXT("MyFloat: %f"), MyFloat);
	UE_LOG(LogTemp, Display, TEXT("*FloatPtr: %f"), *FloatPtr);

	UE_LOG(LogTemp, Display, TEXT("&MyFloat: %p"), &MyFloat);
	UE_LOG(LogTemp, Display, TEXT("FloatPtr: %p"), FloatPtr);

	// ---

	FVector MyVector = FVector(1.0f, 1.0f, 1.0f);
	FVector* VectorPtr = &MyVector;

	(*VectorPtr).X = 2.0f;
	VectorPtr->Y = 3.0f;
	VectorPtr->Z = 4.0f;

	UE_LOG(LogTemp, Display, TEXT("MyVector: %s"), *VectorPtr->ToCompactString());
}


// Called every frame
void UMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
}

