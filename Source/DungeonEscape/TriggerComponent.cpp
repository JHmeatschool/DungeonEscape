// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponent.h"

UTriggerComponent::UTriggerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UTriggerComponent::BeginPlay()
{
	Super::BeginPlay();

	if (MoverActor) //MoverActor != nullptr
	{
		Mover = MoverActor->FindComponentByClass<UMover>();
		if (Mover) //Mover != nullptr
		{
			UE_LOG(LogTemp, Display, TEXT("Successfully found the mover component!"));
			Mover->ShouldMove = true;
		}
		else
		{
			UE_LOG(LogTemp, Display, TEXT("Failed to find mover component!"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("MoverActor is nullptr"));
	}
}

void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


}
