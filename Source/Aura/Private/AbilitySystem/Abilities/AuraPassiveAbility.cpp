


#include "AbilitySystem/Abilities/AuraPassiveAbility.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"

void UAuraPassiveAbility::ActivateAbility(
	const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (UAuraAbilitySystemComponent* AuraAsc = Cast<UAuraAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetAvatarActorFromActorInfo())))
	{
		if (AuraAsc->DeactivatedPassiveAbility.IsBoundToObject(this))
		{
			AuraAsc->DeactivatedPassiveAbility.AddUObject(this, &ThisClass::OnDeactivated);
		}
	}
}

void UAuraPassiveAbility::OnDeactivated(const FGameplayTag& AbilityTag)
{
	if (AbilityTags.HasTag(AbilityTag))
	{
		UAuraAbilitySystemComponent* AuraAsc = Cast<UAuraAbilitySystemComponent>(
			UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetAvatarActorFromActorInfo()));

		if (AuraAsc)
		{
			AuraAsc->DeactivatedPassiveAbility.RemoveAll(this);
		}
		
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
	}
}
